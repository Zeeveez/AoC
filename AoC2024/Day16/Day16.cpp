#include "Day16.h"

#include <regex>
#include <queue>
#include <unordered_set>
#include <iostream>

namespace AoC2024 {
    namespace Day16 {
        std::tuple<int, int, int, int> GetStartAndEnd(const std::vector<std::string>& input) {
            int startX = 0;
            int startY = 0;
            int endX = 0;
            int endY = 0;

            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (input[y][x] == 'S') {
                        startX = x;
                        startY = y;
                    }
                    if (input[y][x] == 'E') {
                        endX = x;
                        endY = y;
                    }
                }
            }

            return { startX, startY, endX, endY };
        }

        void BestPath(const std::vector<std::string>& input, int x, int y, int dx, int dy, int tx, int ty, std::vector<int>& seen, std::vector<std::vector<uint64_t>>& scoresToTiles, uint64_t score, uint64_t& bestScore) {

            if (score > bestScore) {
                return;
            }
            if (score > scoresToTiles[(dx > 0) * 2 + (dy > 0)][y * input.size() + x]) {
                return;
            }
            scoresToTiles[(dx > 0) * 2 + (dy > 0)][y * input.size() + x] = score;
            if (input[y][x] == '#') {
                return;
            }

            if (seen[y * input.size() + x]) {
                return;
            }
            if (x == tx && y == ty) {
                bestScore = std::min(score, bestScore);
                return;
            }


            seen[y * input.size() + x] = true;
            if (dx == 1) {
                BestPath(input, x + 1, y, 1, 0, tx, ty, seen, scoresToTiles, score + 1, bestScore);
                BestPath(input, x, y + 1, 0, 1, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
                BestPath(input, x, y - 1, 0, -1, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
            }
            else if (dx == -1) {
                BestPath(input, x - 1, y, -1, 0, tx, ty, seen, scoresToTiles, score + 1, bestScore);
                BestPath(input, x, y + 1, 0, 1, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
                BestPath(input, x, y - 1, 0, -1, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
            }
            else if (dy == 1) {
                BestPath(input, x + 1, y, 1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
                BestPath(input, x - 1, y, -1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
                BestPath(input, x, y + 1, 0, 1, tx, ty, seen, scoresToTiles, score + 1, bestScore);
            }
            else if (dy == -1) {
                BestPath(input, x + 1, y, 1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
                BestPath(input, x - 1, y, -1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore);
                BestPath(input, x, y - 1, 0, -1, tx, ty, seen, scoresToTiles, score + 1, bestScore);
            }
            seen[y * input.size() + x] = false;
            return;
        }

        void BestTiles(const std::vector<std::string>& input, int x, int y, int dx, int dy, int tx, int ty, std::vector<int>& seen, std::vector<std::vector<uint64_t>>& scoresToTiles, uint64_t score, uint64_t bestScore, std::unordered_set<int>& bestTiles) {

            if (score > bestScore) {
                return;
            }
            if (score > scoresToTiles[(dx > 0) * 2 + (dy > 0)][y * input.size() + x]) {
                return;
            }
            if (input[y][x] == '#') {
                return;
            }

            if (seen[y * input.size() + x]) {
                return;
            }
            if (x == tx && y == ty && score == bestScore) {
                for (size_t i = 0; i < seen.size(); i++) {
                    if (seen[i]) {
                        bestTiles.insert(i);
                    }
                }
                return;
            }


            seen[y * input.size() + x] = true;
            if (dx == 1) {
                BestTiles(input, x + 1, y, 1, 0, tx, ty, seen, scoresToTiles, score + 1, bestScore, bestTiles);
                BestTiles(input, x, y + 1, 0, 1, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
                BestTiles(input, x, y - 1, 0, -1, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
            }
            else if (dx == -1) {
                BestTiles(input, x - 1, y, -1, 0, tx, ty, seen, scoresToTiles, score + 1, bestScore, bestTiles);
                BestTiles(input, x, y + 1, 0, 1, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
                BestTiles(input, x, y - 1, 0, -1, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
            }
            else if (dy == 1) {
                BestTiles(input, x + 1, y, 1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
                BestTiles(input, x - 1, y, -1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
                BestTiles(input, x, y + 1, 0, 1, tx, ty, seen, scoresToTiles, score + 1, bestScore, bestTiles);
            }
            else if (dy == -1) {
                BestTiles(input, x + 1, y, 1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
                BestTiles(input, x - 1, y, -1, 0, tx, ty, seen, scoresToTiles, score + 1001, bestScore, bestTiles);
                BestTiles(input, x, y - 1, 0, -1, tx, ty, seen, scoresToTiles, score + 1, bestScore, bestTiles);
            }
            seen[y * input.size() + x] = false;
            return;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [sx, sy, ex, ey] = GetStartAndEnd(input);
            std::vector<int> seen(input.size() * input[0].size(), false);
            std::vector<std::vector<uint64_t>> scoresToTiles = {};
            for (int i = 0; i < 4; i++) {
                std::vector<uint64_t> s(input.size() * input[0].size(), std::numeric_limits<uint64_t>::max());
                scoresToTiles.push_back(s);
            }


            uint64_t res = std::numeric_limits<uint64_t>::max();
            BestPath(input, sx, sy, 1, 0, ex, ey, seen, scoresToTiles, 0, res);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [sx, sy, ex, ey] = GetStartAndEnd(input);
            std::vector<int> seen(input.size() * input[0].size(), false);
            std::vector<std::vector<uint64_t>> scoresToTiles = {};
            for (int i = 0; i < 4; i++) {
                std::vector<uint64_t> s(input.size() * input[0].size(), std::numeric_limits<uint64_t>::max());
                scoresToTiles.push_back(s);
            }


            uint64_t bestScore = std::numeric_limits<uint64_t>::max();
            BestPath(input, sx, sy, 1, 0, ex, ey, seen, scoresToTiles, 0, bestScore);

            std::unordered_set<int> bestTiles = {};
            BestTiles(input, sx, sy, 1, 0, ex, ey, seen, scoresToTiles, 0, bestScore, bestTiles);

            int res = bestTiles.size() + 1; // count end

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}