#include "Day09.h"

#include <array>
#include <queue>
#include <algorithm>

namespace AoC2015 {
    namespace Day09 {
        const std::array<std::pair<int, int>, 4> OFFSETS = { { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } } };

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

        int LowPointRiskLevel(const std::vector<std::vector<int>>& grid, int x, int y) {
            for (auto& offset : OFFSETS) {
                int nx = x + offset.first;
                int ny = y + offset.second;
                if (ny >= 0 && ny < grid.size() && nx >= 0 && nx < grid[ny].size()) {
                    if (grid[ny][nx] <= grid[y][x]) {
                        return 0;
                    }
                }
            }
            return grid[y][x] + 1;
        }

        int FloodFill(std::vector<std::vector<int>>& grid, int x, int y) {
            std::queue<std::pair<int, int>> queue = {};
            queue.emplace(x, y);
            int replacements = 0;

            while (queue.size()) {
                auto currentCell = queue.front(); queue.pop();
                if (grid[currentCell.second][currentCell.first] != 9) {
                    grid[currentCell.second][currentCell.first] = 9;
                    replacements++;
                    for (auto& offset : OFFSETS) {
                        int nx = currentCell.first + offset.first;
                        int ny = currentCell.second + offset.second;
                        if (ny >= 0 && ny < grid.size() && nx >= 0 && nx < grid[ny].size()) {
                            queue.emplace(nx, ny);
                        }
                    }
                }
            }
            return replacements;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto grid = PreProcessInput(input);
            int risk = 0;
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    risk += LowPointRiskLevel(grid, x, y);
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { risk, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto grid = PreProcessInput(input);
            std::vector<int> basinSizes = {};
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    if (grid[y][x] != 9) {
                        basinSizes.push_back(FloodFill(grid, x, y));
                    }
                }
            }
            std::sort(basinSizes.begin(), basinSizes.end(), std::greater<>());
            auto endTime = std::chrono::high_resolution_clock::now();
            return { basinSizes[0] * basinSizes[1] * basinSizes[2], endTime - startTime };
        }
    }
}