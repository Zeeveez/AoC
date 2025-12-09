#include "Day08.h"

namespace AoC2022 {
    namespace Day08 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<int>> grid = {};
            for (auto& line : input) {
                grid.push_back({});
                for (auto& c : line) {
                    grid[grid.size() - 1].push_back(c - '0');
                }
            }
            return grid;
        }

        bool IsTreeVisible(const std::vector<std::vector<int>>& grid, int tx, int ty) {
            for (int x = 0; x <= tx; x++) {
                if (x == tx) {
                    return true;
                }
                else if (grid[ty][x] >= grid[ty][tx]) {
                    break;
                }
            }
            for (int x = grid[ty].size() - 1; x >= tx; x--) {
                if (x == tx) {
                    return true;
                }
                else if (grid[ty][x] >= grid[ty][tx]) {
                    break;
                }
            }
            for (int y = 0; y <= ty; y++) {
                if (y == ty) {
                    return true;
                }
                else if (grid[y][tx] >= grid[ty][tx]) {
                    break;
                }
            }
            for (int y = grid.size() - 1; y >= ty; y--) {
                if (y == ty) {
                    return true;
                }
                else if (grid[y][tx] >= grid[ty][tx]) {
                    break;
                }
            }
            return false;
        }

        uint64_t GetTreeViewScore(const std::vector<std::vector<int>>& grid, int tx, int ty) {
            int upScore = 0;
            for (int y = ty - 1; y > -1; y--) {
                upScore++;
                if (grid[y][tx] >= grid[ty][tx]) {
                    break;
                }
            }

            int leftScore = 0;
            for (int x = tx - 1; x > -1; x--) {
                leftScore++;
                if (grid[ty][x] >= grid[ty][tx]) {
                    break;
                }
            }

            int downScore = 0;
            for (int y = ty + 1; y < grid.size(); y++) {
                downScore++;
                if (grid[y][tx] >= grid[ty][tx]) {
                    break;
                }
            }

            int rightScore = 0;
            for (int x = tx + 1; x < grid[ty].size(); x++) {
                rightScore++;
                if (grid[ty][x] >= grid[ty][tx]) {
                    break;
                }
            }

            return upScore * leftScore * downScore * rightScore;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto grid = PreProcessInput(input);

            uint64_t count = 0;
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    if (IsTreeVisible(grid, x, y)) {
                        count++;
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { count, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto grid = PreProcessInput(input);

            uint64_t score = 0;
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    score = std::max(score, GetTreeViewScore(grid, x, y));
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - startTime };
        }
    }
}