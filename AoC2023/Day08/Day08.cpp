#include "Day08.h"

#include <iostream>

namespace AoC2023 {
    namespace Day08 {
        std::unordered_map<int, std::pair<int, int>> LoadPaths(const std::vector<std::string>& input) {
            std::unordered_map<int, std::pair<int, int>> paths = {};
            for (size_t i = 2; i < input.size(); i++) {
                int from = (input[i][0] - 'A') * 26 * 26 + (input[i][1] - 'A') * 26 + (input[i][2] - 'A');
                int toL = (input[i][7] - 'A') * 26 * 26 + (input[i][8] - 'A') * 26 + (input[i][9] - 'A');
                int toR = (input[i][12] - 'A') * 26 * 26 + (input[i][13] - 'A') * 26 + (input[i][14] - 'A');
                paths[from] = { toL, toR };
            }
            return paths;
        }

        size_t GetDistance(const std::string& inst, const std::unordered_map<int, std::pair<int, int>>& paths, int start, int end) {
            size_t distance = 0;
            while (start != end) {
                if (inst[distance++ % inst.length()] == 'L') {
                    start = paths.at(start).first;
                }
                else {
                    start = paths.at(start).second;
                }
                if (distance > 1e6) {
                    return std::numeric_limits<size_t>::max();
                }
            }
            return distance;
        }

        std::unordered_map<int, int> GetDistances(const std::string& inst, const std::unordered_map<int, std::pair<int, int>>& paths) {
            std::unordered_map<int, int> output = {};

            for (auto& [start, _] : paths) {
                if (start % 26 != 0) { continue; }
                size_t pos = start;
                size_t distance = 0;
                while (pos % 26 != 25) {
                    if (inst[distance++ % inst.length()] == 'L') {
                        pos = paths.at(pos).first;
                    }
                    else {
                        pos = paths.at(pos).second;
                    }
                }
                output[start] = distance;
            }

            return output;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto paths = LoadPaths(input);
            uint64_t score = GetDistance(input[0], paths, 0, 17575);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto paths = LoadPaths(input);
            auto startEndDistances = GetDistances(input[0], paths);
            uint64_t score = 1;
            for (auto& [_, distance] : startEndDistances) {
                score = std::_Lcm(score, distance);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }
    }
}

/*
LRZ

AAA = (AAB, XXX)
AAB = (XXX, AAZ)
AAZ = (AAB, XXX)
ZZA = (ZZB, XXX)
ZZB = (ZZC, ZZC)
ZZC = (ZZZ, ZZZ)
ZZZ = (ZZB, ZZB)
XXX = (XXX, XXX)
*/