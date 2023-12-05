#include "Day05.h"

#include <iostream>

namespace AoC2023 {
    namespace Day05 {
        RangeMap::RangeMap(const std::string& input) {
            std::istringstream iss(input);
            iss >> destinationStart;
            iss >> sourceStart;
            iss >> size;
        }

        bool RangeMap::Contains(size_t v) {
            return v >= sourceStart
                && v < sourceStart + size;
        }

        size_t RangeMap::Map(size_t v) {
            return destinationStart + v - sourceStart;
        }

        SourceMap::SourceMap(const std::vector<std::string>& input, size_t& i) {
            source = input[i].substr(0, input[i].find('-'));
            destination = input[i].substr(input[i].find('-') + 4, input[i].find(' ') - source.length() - 4);

            while (++i < input.size() && input[i] != "") {
                maps.push_back(RangeMap(input[i]));
            }
        }

        size_t SourceMap::Map(size_t v) {
            for (auto& map : maps) {
                if (map.Contains(v)) {
                    return map.Map(v);
                }
            }
            return v;
        }

        Almanac::Almanac(const std::vector<std::string>& input) {
            size_t i = 1;
            while (++i < input.size()) {
                SourceMap map = SourceMap(input, i);
                sourceMaps[map.source] = map;
            }
        }

        size_t Almanac::Traverse(std::string source, std::string destination, size_t value) {
            do {
                if (sourceMaps[source].destination == destination) {
                    return sourceMaps[source].Map(value);
                }
                value = sourceMaps[source].Map(value);
                source = sourceMaps[source].destination;
            } while (true);
        }



        std::pair<std::vector<size_t>, Almanac> ParseInput(const std::vector<std::string>& input) {
            std::istringstream iss(input[0]);
            std::string temp;
            iss >> temp; // Discard "seeds:"

            std::vector<size_t> seeds = {};
            size_t token;
            while (iss >> token) {
                seeds.push_back(token);
            }

            Almanac almanac = Almanac(input);

            return { seeds, almanac };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [seeds, almanac] = ParseInput(input);

            size_t score = std::numeric_limits<size_t>::max();
            for (auto& seed : seeds) {
                score = std::min(score, almanac.Traverse("seed", "location", seed));
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto [seeds, almanac] = ParseInput(input);

            size_t score = std::numeric_limits<size_t>::max();
            for (size_t i = 0; i < seeds.size(); i += 2) {
                for (size_t j = 0; j <= seeds[i + 1] - 1; j++) {
                    score = std::min(score, almanac.Traverse("seed", "location", seeds[i] + j));
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }
    }
}