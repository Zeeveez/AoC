#include "Day21.h"

#include <iostream>

namespace AoC2023::Day21 {
    std::pair<int, int> FindStart(const std::vector<std::string>& input) {
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                if (input[y][x] == 'S') {
                    return { x, y };
                }
            }
        }
        return { -1, -1 };
    }

    std::set<std::pair<int, int>> GetNewPositions(const std::vector<std::string>& input, const std::set<std::pair<int, int>>& currentPositions) {
        const std::set<std::pair<int, int>> offsets = {
            { 1, 0 },
            { -1, 0 },
            { 0, 1 },
            { 0, -1 },
        };
        std::set<std::pair<int, int>> newPositions = {};

        for (auto& pos : currentPositions) {
            for (auto& offset : offsets) {
                int x = pos.first + offset.first;
                int y = pos.second + offset.second;
                if (y >= 0 && y < input.size() && x >= 0 && x < input[y].size()) {
                    if (input[y][x] != '#') {
                        newPositions.insert({ x, y });
                    }
                }
            }
        }

        return newPositions;
    }

    std::pair<uint64_t, uint64_t> GetCounts(const std::vector<std::string>& input, std::pair<int, int> start, int maxIter) {
        uint64_t goodTiles = 0;
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                if (input[y][x] != '#') {
                    goodTiles++;
                }
            }
        }
        std::set<std::pair<int, int>> currentPositions = { start };
        std::set<std::pair<int, int>> lastPositions = { };
        int iter = 0;
        while (currentPositions.size() + lastPositions.size() != goodTiles && iter < maxIter) {
            iter++;
            auto newPositions = GetNewPositions(input, currentPositions);
            lastPositions = currentPositions;
            currentPositions = newPositions;
        }


        return { lastPositions.size(), currentPositions.size() };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::set<std::pair<int, int>> positions = { FindStart(input) };

        int64_t score = GetCounts(input, { input[0].size() / 2 , input.size() / 2 }, 64).second;

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        auto topLeft = GetCounts(input, { input[0].size() - 1, input.size() - 1 }, input.size() + input[0].size());
        auto left = GetCounts(input, { input[0].size() - 1, input.size() / 2 }, input.size() + input[0].size());
        auto bottomLeft = GetCounts(input, { input[0].size() - 1, 0 }, input.size() + input[0].size());
        auto top = GetCounts(input, { input[0].size() / 2, input.size() - 1 }, input.size() + input[0].size());
        auto middle = GetCounts(input, { input[0].size() / 2, input.size() / 2 }, input.size() + input[0].size());
        auto bottom = GetCounts(input, { input[0].size() / 2, 0 }, input.size() + input[0].size());
        auto topRight = GetCounts(input, { 0, input.size() - 1 }, input.size() + input[0].size());
        auto right = GetCounts(input, { 0, input.size() / 2 }, input.size() + input[0].size());
        auto bottomRight = GetCounts(input, { 0, 0 }, input.size() + input[0].size());


        int steps = 1000;

        uint64_t score = 0;

        for (int dx = -steps / (int)input[0].size() - 1; dx < steps / (int)input[0].size() + 1; dx++) {
            for (int dy = -steps / (int)input.size() - 1; dy < steps / (int)input.size() + 1; dy++) {
                int startSteps = (dx ? std::abs(dx) * input[0].size() - input[0].size() / 2 : 0) + (dy ? std::abs(dy) * input.size() - input.size() / 2 : 0);
                int remainingSteps = steps - startSteps;
                if(remainingSteps <= 0){ continue; }
                if (remainingSteps < input.size() + input[0].size()) {
                    int startX = dx < 0 ? input[0].size() - 1 : (dx == 0 ? input[0].size() / 2 : 0);
                    int startY = dy < 0 ? input.size() - 1 : (dy == 0 ? input.size() / 2 : 0);
                    auto counts = GetCounts(input, { startX, startY }, remainingSteps);
                    score += startSteps % 2 ? counts.first : counts.second;
                }
                else {
                    if (dx == 0 && dy == 0) {
                        score += startSteps % 2 ? middle.first : middle.second;
                    }
                    else if (dx < 0 && dy < 0) {
                        score += startSteps % 2 ? topLeft.first : topLeft.second;
                    }
                    else if (dx < 0 && dy == 0) {
                        score += startSteps % 2 ? left.first : left.second;
                    }
                    else if (dx < 0 && dy > 0) {
                        score += startSteps % 2 ? bottomLeft.first : bottomLeft.second;
                    }
                    else if (dx == 0 && dy < 0) {
                        score += startSteps % 2 ? top.first : top.second;
                    }
                    else if (dx == 0 && dy > 0) {
                        score += startSteps % 2 ? bottom.first : bottom.second;
                    }
                    else if (dx > 0 && dy < 0) {
                        score += startSteps % 2 ? topRight.first : topRight.second;
                    }
                    else if (dx > 0 && dy == 0) {
                        score += startSteps % 2 ? right.first : right.second;
                    }
                    else if (dx > 0 && dy > 0) {
                        score += startSteps % 2 ? bottomRight.first : bottomRight.second;
                    }
                }
            }
        }


        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}