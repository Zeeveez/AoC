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

    std::unordered_map<int64_t, std::set<int64_t>> ExpandUniverse(const std::unordered_map<int64_t, std::set<int64_t>>& universe, int64_t width, int64_t height, int64_t expansionAmount) {
        std::unordered_map<int64_t, std::set<int64_t>> newUniverse;

        int64_t widthExpansions = 0;
        for (int64_t x = 0; x < width; x++) {
            if (!universe.contains(x)) {
                widthExpansions++;
            }
            else {
                newUniverse.insert({ x + widthExpansions * expansionAmount, universe.at(x) });
            }
        }

        for (int64_t y = height - 1; y > -1; y--) {
            bool empty = true;
            for (const auto& row : universe) {
                if (row.second.contains(y)) {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                for (int64_t moveY = height; moveY > y; moveY--) {
                    for (auto& row : newUniverse) {
                        if (row.second.contains(moveY)) {
                            row.second.erase(moveY);
                            row.second.insert(moveY + expansionAmount);
                        }
                    }
                }
                height += expansionAmount;
            }
        }

        return newUniverse;
    }

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto starttime = std::chrono::high_resolution_clock::now();

        auto universe = LoadUniverse(input);
        universe = ExpandUniverse(universe, input[0].size(), input.size(), 1);

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

                        score += std::abs(x1 - x2) + std::abs(y1 - y2);
                    }
                }
            }
        }

        auto endtime = std::chrono::high_resolution_clock::now();
        return { score, endtime - starttime };
    }

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto starttime = std::chrono::high_resolution_clock::now();

        auto universe = LoadUniverse(input);
        universe = ExpandUniverse(universe, input[0].size(), input.size(), 999999);

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

                        score += std::abs(x1 - x2) + std::abs(y1 - y2);
                    }
                }
            }
        }

        auto endtime = std::chrono::high_resolution_clock::now();
        return { score, endtime - starttime };
    }
}