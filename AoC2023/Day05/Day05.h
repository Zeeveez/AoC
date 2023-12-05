#ifndef DAY05_H
#define DAY05_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <map>

namespace AoC2023 {
    namespace Day05 {
        class RangeMap {
        public:
            size_t destinationStart;
            size_t sourceStart;
            size_t size;

            RangeMap() = default;
            RangeMap(const std::string& input);

            bool Contains(size_t v);
            size_t Map(size_t v);
        };

        class SourceMap {
        public:
            std::string source;
            std::string destination;
            std::vector<RangeMap> maps;

            SourceMap() = default;
            SourceMap(const std::vector<std::string>& input, size_t& i);

            size_t Map(size_t v);
        };

        class Almanac {
        public:
            std::map<std::string, SourceMap> sourceMaps;

            Almanac(const std::vector<std::string>& input);
            size_t Traverse(std::string source, std::string destination, size_t value);
        };

        std::pair<std::vector<size_t>, Almanac> ParseInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif