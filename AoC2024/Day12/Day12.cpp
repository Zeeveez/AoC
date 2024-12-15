#include "Day12.h"

#include <queue>
#include <set>
#include <unordered_map>
#include <iostream>
#include <algorithm>

namespace AoC2024 {
    namespace Day12 {
        std::set<std::pair<int, int>> GetShape(const std::vector<std::string>& map, int x, int y, std::set<std::pair<int, int>>& seen) {
            std::queue<std::pair<int, int>> queue = {};
            std::set<std::pair<int, int>> shape = {};
            char target = map[y][x];
            queue.push({ x, y });
            while (!queue.empty()) {
                auto [x, y] = queue.front(); queue.pop();
                if (map[y][x] != target) { continue; }
                if (seen.contains({ x, y })) { continue; }
                seen.insert({ x, y });
                if (x > 0) {
                    queue.push({ x - 1, y });
                }
                if (y > 0) {
                    queue.push({ x, y - 1 });
                }
                if (x < map.size() - 1) {
                    queue.push({ x + 1, y });
                }
                if (y < map.size() - 1) {
                    queue.push({ x, y + 1 });
                }
                shape.insert({ x, y });
            }
            return shape;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            std::set<std::pair<int, int>> seen = {};

            uint64_t res = 0;
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (!seen.contains({ x, y })) {
                        auto shape = GetShape(input, x, y, seen);
                        uint64_t peri = 0;
                        for (auto& cell : shape) {
                            if (!shape.contains({ cell.first - 1, cell.second })) { peri++; }
                            if (!shape.contains({ cell.first + 1, cell.second })) { peri++; }
                            if (!shape.contains({ cell.first, cell.second - 1 })) { peri++; }
                            if (!shape.contains({ cell.first, cell.second + 1 })) { peri++; }
                        }
                        res += peri * shape.size();
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            std::set<std::pair<int, int>> seen = {};

            uint64_t res = 0;
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (!seen.contains({ x, y })) {
                        auto shape = GetShape(input, x, y, seen);

                        // Shamelessly stolen from hyperneutrino while I figure out how tf it works, thanks hyperneutrino:
                        // https://github.com/hyperneutrino/advent-of-code/blob/main/2024/day12p2.py
                        std::set<std::pair<float, float>> ccs;
                        for (auto& cell : shape) {
                            ccs.insert({ cell.first - 0.5, cell.second - 0.5 });
                            ccs.insert({ cell.first + 0.5, cell.second - 0.5 });
                            ccs.insert({ cell.first + 0.5, cell.second + 0.5 });
                            ccs.insert({ cell.first - 0.5, cell.second + 0.5 });
                        }

                        uint64_t corners = 0;
                        for (auto& cc : ccs) {
                            int c = 0;
                            int n = 0;
                            if (shape.contains({ cc.first - 0.5, cc.second - 0.5 })) { c++; n += 8; }
                            if (shape.contains({ cc.first + 0.5, cc.second - 0.5 })) { c++; n += 4; }
                            if (shape.contains({ cc.first + 0.5, cc.second + 0.5 })) { c++; n += 2; }
                            if (shape.contains({ cc.first - 0.5, cc.second + 0.5 })) { c++; n++; }
                            if (c == 1) {
                                corners++;
                            }
                            else if (c == 2) {
                                if (n == 10 || n == 5) {
                                    corners += 2;
                                }
                            }
                            else if (c == 3) {
                                corners++;
                            }
                        }

                        res += shape.size() * corners;
                    }
                }
            }
            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}