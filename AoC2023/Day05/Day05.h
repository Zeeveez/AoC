#ifndef DAY05_H
#define DAY05_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <map>
#include <optional>

namespace AoC2023::Day05 {
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
    };

    std::tuple<std::vector<RangeMap>, std::vector<RangeMap>, std::vector<RangeMap>> ReMap(RangeMap a, RangeMap b);


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

        Almanac(const std::vector<std::string>& input);
        size_t Traverse(std::string source, std::string destination, size_t value);
        void Flatten(const std::string& start);
    };

    std::pair<std::vector<size_t>, Almanac> ParseInput(const std::vector<std::string>& input);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif