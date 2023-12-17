#include "Day17.h"

#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <map>

namespace AoC2023::Day17 {
    std::vector<std::vector<int>> ParseInput(const std::vector<std::string>& input) {
        std::vector<std::vector<int>> grid = {};
        for (auto& line : input) {
            grid.push_back({});
            for (auto& c : line) {
                grid.back().push_back(c - '0');
            }
        }
        return grid;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto grid = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::map<std::pair<size_t, size_t>, std::vector<std::pair<int, int>>> DIRS = {
            { { 1,  0 }, { /*{ 1,  0 },*/ { 0, 1 }, { 0, -1 } } },
            { {-1,  0 }, { /*{-1,  0 },*/ { 0, 1 }, { 0, -1 } } },
            { { 0,  1 }, { /*{ 0,  1 },*/ { 1, 0 }, {-1,  0 } } },
            { { 0, -1 }, { /*{ 0, -1 },*/ { 1, 0 }, {-1,  0 } } }
        };

        std::map<std::tuple<std::pair<size_t, size_t>, std::pair<int, int>, int>, int64_t> seen = {};
        std::queue<std::tuple<std::pair<size_t, size_t>, std::pair<int, int>, int, int64_t>> moves = {};

        moves.push({ { 0, 0 }, { 1, 0 }, 0, -grid[0][0] });
        moves.push({ { 0, 0 }, { 0, 1 }, 0, -grid[0][0] });

        int64_t score = std::numeric_limits<int64_t>::max();

        while (moves.size()) {
            auto [pos, dir, moveCount, totalCost] = moves.front(); moves.pop();

            if (pos.second < 0 || pos.second >= grid.size() || pos.first < 0 || pos.first >= grid[pos.second].size()) { continue; }
            totalCost += grid[pos.second][pos.first];

            if (seen.contains({ pos, dir, moveCount })) {
                if (seen[{ pos, dir, moveCount }] <= totalCost) {
                    continue;
                }
            }

            for (int i = moveCount; i < 3; i++) {
                if (!seen.contains({ pos, dir, i })) {
                    seen[{ pos, dir, i }] = totalCost;
                }
                else {
                    if (seen[{ pos, dir, i }] > totalCost) {
                        seen[{ pos, dir, i }] = totalCost;
                    }
                }
            }

            if (pos.second == grid.size() - 1 && pos.first == grid[pos.second].size() - 1) {
                score = std::min(score, totalCost);
                continue;
            }


            std::vector<std::pair<std::pair<int, int>, int>> nextDirs = {};
            if (moveCount < 3) {
                nextDirs.push_back({ dir, moveCount + 1 });
            }
            for (auto& nextDir : DIRS[dir]) {
                nextDirs.push_back({ nextDir, 1 });
            }

            std::vector<std::pair<size_t, size_t>> nextPoss = {};
            for (auto& nextDir : nextDirs) {
                moves.push({
                                { pos.first + nextDir.first.first, pos.second + nextDir.first.second },
                                nextDir.first,
                                nextDir.second,
                                totalCost
                           });
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto grid = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::map<std::pair<size_t, size_t>, std::vector<std::pair<int, int>>> DIRS = {
            { { 1,  0 }, { /*{ 1,  0 },*/ { 0, 1 }, { 0, -1 } } },
            { {-1,  0 }, { /*{-1,  0 },*/ { 0, 1 }, { 0, -1 } } },
            { { 0,  1 }, { /*{ 0,  1 },*/ { 1, 0 }, {-1,  0 } } },
            { { 0, -1 }, { /*{ 0, -1 },*/ { 1, 0 }, {-1,  0 } } }
        };

        std::map<std::tuple<std::pair<size_t, size_t>, std::pair<int, int>, int>, int64_t> seen = {};
        std::queue<std::tuple<std::pair<size_t, size_t>, std::pair<int, int>, int, int64_t>> moves = {};

        moves.push({ { 0, 0 }, { 1, 0 }, 0, -grid[0][0] });
        moves.push({ { 0, 0 }, { 0, 1 }, 0, -grid[0][0] });

        int64_t score = std::numeric_limits<int64_t>::max();

        while (moves.size()) {
            auto [pos, dir, moveCount, totalCost] = moves.front(); moves.pop();

            if (pos.second < 0 || pos.second >= grid.size() || pos.first < 0 || pos.first >= grid[pos.second].size()) { continue; }
            totalCost += grid[pos.second][pos.first];

            if (seen.contains({ pos, dir, moveCount })) {
                if (seen[{ pos, dir, moveCount }] <= totalCost) {
                    continue;
                }
                else {
                    seen[{ pos, dir, moveCount }] = totalCost;
                }
            }else{
                seen[{ pos, dir, moveCount }] = totalCost;
            }

            if (pos.second == grid.size() - 1 && pos.first == grid[pos.second].size() - 1 && moveCount > 3) {
                score = std::min(score, totalCost);
                continue;
            }


            std::vector<std::pair<std::pair<int, int>, int>> nextDirs = {};
            if (moveCount < 10) {
                nextDirs.push_back({ dir, moveCount + 1 });
            }
            if (moveCount > 3) {
                for (auto& nextDir : DIRS[dir]) {
                    nextDirs.push_back({ nextDir, 1 });
                }
            }

            std::vector<std::pair<size_t, size_t>> nextPoss = {};
            for (auto& nextDir : nextDirs) {
                moves.push({
                                { pos.first + nextDir.first.first, pos.second + nextDir.first.second },
                                nextDir.first,
                                nextDir.second,
                                totalCost
                           });
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}