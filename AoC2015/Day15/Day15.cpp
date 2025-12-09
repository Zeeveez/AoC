#include "Day15.h"

#include <queue>
#include <limits>
#include <algorithm>

namespace AoC2015 {
    namespace Day15 {
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

        std::vector<std::vector<int>> ConvertToFullMap(const std::vector<std::vector<int>>& input) {
            std::vector<std::vector<int>> grid = {};
            for (auto& row : input) {
                grid.push_back({});
                for (int i = 0; i < 5; i++) {
                    for (auto& c : row) {
                        int v = c + i;
                        v -= (v > 9 ? 9 : 0);
                        grid[grid.size() - 1].push_back(v);
                    }
                }
            }
            for (int i = 1; i < 5; i++) {
                for (int j = 0; j < input.size(); j++) {
                    grid.push_back({});
                    for (int k = 0; k < grid[0].size(); k++) {
                        int v = grid[j][k] + i;
                        v -= (v > 9 ? 9 : 0);
                        grid[grid.size() - 1].push_back(v);
                    }
                }
            }
            return grid;
        }

        std::vector<std::vector<int>> FindCosts(const std::vector<std::vector<int>>& input) {
            const std::vector<std::pair<int, int>> possibleNeighbours = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
            std::vector<std::vector<int>> costs = {};
            for (int i = 0; i < input.size(); i++) {
                costs.push_back({});
                for (int j = 0; j < input[0].size(); j++) {
                    costs[i].push_back(std::numeric_limits<int>::max());
                }
            }
            costs[0][0] = 0;
            std::queue<std::pair<int, int>> queue = {};
            queue.push({ 0, 0 });

            while (!queue.empty()) {
                auto pos = queue.front(); queue.pop();
                for (auto& neighbour : possibleNeighbours) {
                    int x = pos.first + neighbour.first;
                    if (x < 0 || x >= input[0].size()) { continue; }
                    int y = pos.second + neighbour.second;
                    if (y < 0 || y >= input.size()) { continue; }

                    int newCost = input[y][x] + costs[pos.second][pos.first];
                    if (costs[y][x] > newCost) {
                        costs[y][x] = newCost;
                        queue.push({ x, y });
                    }
                }
            }
            return costs;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto costs = FindCosts(PreProcessInput(input));

            auto endTime = std::chrono::high_resolution_clock::now();
            return { costs[costs.size() - 1][costs[0].size() - 1], endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto costs = FindCosts(ConvertToFullMap(PreProcessInput(input)));

            auto endTime = std::chrono::high_resolution_clock::now();
            return { costs[costs.size() - 1][costs[0].size() - 1], endTime - startTime };
        }
    }
}