#include "Day11.h"

#include <iostream>
#include <numeric>
#include <queue>

namespace AoC2023::Day11 {
    std::unordered_map<int64_t, std::set<int64_t>> LoadUniverse(const std::vector<std::string>& input) {
        std::unordered_map<int64_t, std::set<int64_t>> output = {};
        for (int64_t y = 0; y < input.size(); y++) {
            for (int64_t x = 0; x < input[y].size(); x++) {
                if (input[y][x] != '#') { continue; }
                if (!output.contains(x)) { output[x] = {}; }
                output[x].insert(y);
            }
        }

        return output;
    }

    std::pair<std::vector<int64_t>, std::vector<int64_t>> GetExpansionsPerDimension(const std::unordered_map<int64_t, std::set<int64_t>>& universe, int64_t width, int64_t height) {
        std::vector<int64_t> widthExpansions = { 0 };
        for (int64_t x = 0; x < width - 1; x++) {
            widthExpansions.push_back(widthExpansions.back() + (universe.contains(x) ? 0 : 1));
        }

        std::vector<int64_t> heightExpansions = { 0 };
        for (int64_t y = 0; y < height - 1; y++) {
            bool empty = true;
            for (const auto& row : universe) {
                if (row.second.contains(y)) {
                    empty = false;
                    break;
                }
            }
            heightExpansions.push_back(heightExpansions.back() + (empty ? 1 : 0));
        }

        return { widthExpansions, heightExpansions };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> Solve(const std::vector<std::string>& input, int64_t expansionAmount) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto universe = LoadUniverse(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        auto expansions = GetExpansionsPerDimension(universe, input[0].size(), input.size());

        uint64_t score = 0;
        std::set<std::pair<int64_t, int64_t>> measuredFrom = {};
        for (auto& [x1, stars1] : universe) {
            for (auto& y1 : stars1) {
                measuredFrom.insert({ x1, y1 });
                for (auto& [x2, stars2] : universe) {
                    for (auto& y2 : stars2) {
                        if (measuredFrom.contains({ x2, y2 })) {
                            continue;
                        }

                        score += std::abs(x1 + expansions.first[x1] * expansionAmount - x2 - expansions.first[x2] * expansionAmount)
                            + std::abs(y1 + expansions.second[y1] * expansionAmount - y2 - expansions.second[y2] * expansionAmount);
                    }
                }
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }


    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        return Solve(input, 1);
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        return Solve(input, 999999);
    }
}