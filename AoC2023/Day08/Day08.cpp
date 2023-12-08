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

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto paths = LoadPaths(input);
            size_t score = 0;

            size_t pos = 0;         // AAA = 0
            while (pos != 17575) {  // ZZZ = 17575
                if (input[0][score++ % input[0].length()] == 'L') {
                    pos = paths.at(pos).first;
                }
                else {
                    pos = paths.at(pos).second;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto paths = LoadPaths(input);
            uint64_t score = 1;

            for (auto& [start, _] : paths) {
                if (start % 26 != 0) { continue; }
                size_t pos = start;
                size_t distance = 0;
                while (pos % 26 != 25) {
                    if (input[0][distance++ % input[0].length()] == 'L') {
                        pos = paths.at(pos).first;
                    }
                    else {
                        pos = paths.at(pos).second;
                    }
                }
                score = std::_Lcm(score, distance);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }
    }
}