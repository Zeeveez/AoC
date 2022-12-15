#include "Day11.h"

#include <queue>

namespace AoC2015 {
    namespace Day11 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<int>> grid = {};
            for (auto& row : input) {
                grid.push_back({});
                for (auto& c : row) {
                    grid[grid.size() - 1].push_back(c - '0');
                }
            }
            return grid;
        }

        int Step(std::vector<std::vector<int>>& grid) {
            std::queue<std::pair<int, int>> queue = {};
            int flashes = 0;

            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    queue.push({ x, y });
                }
            }

            while (queue.size()) {
                auto [x, y] = queue.front(); queue.pop();
                if (grid[y][x] == -1) {
                    continue;
                }
                grid[y][x]++;
                if (grid[y][x] > 9) {
                    flashes++;
                    for (int dx = -1; dx < 2; dx++) {
                        for (int dy = -1; dy < 2; dy++) {
                            if (!(dx == 0 && dy == 0) && (x + dx) > -1 && (y + dy) > -1 && (y + dy) < grid.size() && (x + dx) < grid[y + dy].size()) {
                                queue.push({ x + dx, y + dy });
                            }
                        }
                    }
                    grid[y][x] = -1;
                }
            }

            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    if (grid[y][x] == -1) {
                        grid[y][x] = 0;
                    }
                }
            }

            return flashes;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto grid = PreProcessInput(input);

            int flashes = 0;
            for (int i = 0; i < 100; i++) {
                flashes += Step(grid);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { flashes, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto grid = PreProcessInput(input);

            int steps = 0;
            do {
                steps++;
            } while (Step(grid) != grid.size() * grid[0].size());
            auto endTime = std::chrono::high_resolution_clock::now();
            return { steps, endTime - startTime };
        }
    }
}