#include "Day08.h"

#include <iostream>
#include <numeric>

namespace AoC2023::Day08 {
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

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto paths = LoadPaths(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        size_t score = 0;

        size_t pos = 0;         // AAA = 0
        while (pos != 17575) {  // ZZZ = 17575
            pos = input[0][score++ % input[0].length()] == 'L' ? paths.at(pos).first : paths.at(pos).second;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto paths = LoadPaths(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = 1;

        for (auto& [start, _] : paths) {
            if (start % 26 != 0) { continue; }
            size_t pos = start;
            size_t distance = 0;
            while (pos % 26 != 25) {
                pos = input[0][distance++ % input[0].length()] == 'L' ? paths.at(pos).first : paths.at(pos).second;
            }
            score = std::_Lcm(score, distance);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}