#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <functional>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day08 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day08() : Day() {
            dayNo = 8;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::unordered_map<char, std::vector<std::pair<int, int>>> nodes = {};

        static void AddAntinodesA(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid);
        static void AddAntinodesB(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid);
        uint64_t CountAntinodes(const std::vector<std::string>& grid);
        uint64_t Run(std::function<void(const std::pair<int, int>&, const std::pair<int, int>&, std::vector<std::string>&)> antinodeFunc);
    };
}