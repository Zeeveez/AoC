#pragma once
#include <string>
#include <vector>
#include <map>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day05 : public AoC::Day {
    private:
        class RangeMap {
        public:
            size_t destinationStart;
            size_t sourceStart;
            size_t size;

            RangeMap() = default;
            RangeMap(const std::string& input);
            RangeMap(size_t destinationStart, size_t sourceStart, size_t size);

            bool Contains(size_t v);
            size_t Map(size_t v);
            static std::tuple<std::vector<RangeMap>, std::vector<RangeMap>, std::vector<RangeMap>> ReMap(RangeMap a, RangeMap b);
        };

        class SourceMap {
        public:
            std::string source;
            std::string destination;
            std::vector<RangeMap> maps;

            SourceMap() = default;
            SourceMap(const std::vector<std::string>& input, size_t& i);

            size_t Map(size_t v);
            void MergeIn(const SourceMap& other);
        };

        class Almanac {
        public:
            std::map<std::string, SourceMap> sourceMaps;

            Almanac() = default;
            Almanac(const std::vector<std::string>& input);
            size_t Traverse(std::string source, std::string destination, size_t value);
            void Flatten(const std::string& start);
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day05() : Day() {
            dayNo = 5;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<size_t> seeds = {};
        Almanac almanac;
    };
}