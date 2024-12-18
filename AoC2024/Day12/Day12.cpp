#include "Day12.h"

#include <queue>
#include <set>

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

            std::set<std::pair<int, int>> dirs = {
                { 0, -1 },
                { 0, 1 },
                { 1, 0 },
                { -1, 0 }
            };

            uint64_t res = 0;
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (!seen.contains({ x, y })) {
                        auto shape = GetShape(input, x, y, seen);

                        uint64_t edges = 0;
                        for (auto& dir : dirs) {
                            std::set<std::tuple<int, int>> seenInDir = {};
                            std::pair<int, int> perpDir1 = { dir.first ? 0 : -1, dir.second ? 0 : -1 };
                            std::pair<int, int> perpDir2 = { dir.first ? 0 : 1, dir.second ? 0 : 1 };

                            for (auto& cell : shape) {
                                if (seenInDir.contains(cell)) { continue; }
                                int sx = cell.first;
                                int sy = cell.second;
                                seenInDir.insert({ sx, sy });

                                // Make sure at edge in given direction
                                if (shape.contains({ sx + dir.first, sy + dir.second })) { continue; }

                                edges++;
                                // Follow along edge marking as visited
                                for(int i = 0;; i++){
                                    if(!shape.contains({ sx + perpDir1.first * i, sy + perpDir1.second * i })){ break; }
                                    if(shape.contains({ sx + perpDir1.first * i + dir.first, sy + perpDir1.second * i + dir.second })){ break; }
                                    seenInDir.insert({ sx + perpDir1.first * i, sy + perpDir1.second * i });
                                }
                                for (int i = 0;; i++) {
                                    if (!shape.contains({ sx + perpDir2.first * i, sy + perpDir2.second * i })) { break; }
                                    if (shape.contains({ sx + perpDir2.first * i + dir.first, sy + perpDir2.second * i + dir.second })) { break; }
                                    seenInDir.insert({ sx + perpDir2.first * i, sy + perpDir2.second * i });
                                }
                            }
                        }

                        res += shape.size() * edges;
                    }
                }
            }
            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}