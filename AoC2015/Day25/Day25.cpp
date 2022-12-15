#include "Day25.h"

#include <iostream>

namespace AoC2015 {
    namespace Day25 {
        std::vector<std::vector<char>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<char>> output = {};
            for (auto& line : input) {
                output.push_back({});
                for (auto& c : line) {
                    output[output.size() - 1].push_back(c);
                }
            }
            return output;
        }

        bool Step(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& willMove) {
            bool movement = false;
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[0].size(); x++) {
                    willMove[y][x] = grid[y][x] == '>' && grid[y][(x + 1) % grid[0].size()] == '.';
                }
            }
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[0].size(); x++) {
                    if (willMove[y][x]) {
                        grid[y][x] = '.';
                        grid[y][(x + 1) % grid[0].size()] = '>';
                        movement = true;
                    }
                }
            }

            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[0].size(); x++) {
                    willMove[y][x] = grid[y][x] == 'v' && grid[(y + 1) % grid.size()][x] == '.';
                }
            }
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[0].size(); x++) {
                    if (willMove[y][x]) {
                        grid[y][x] = '.';
                        grid[(y + 1) % grid.size()][x] = 'v';
                        movement = true;
                    }
                }
            }

            return movement;
        }

        uint64_t CountSteps(std::vector<std::vector<char>>& grid) {
            std::vector<std::vector<bool>> willMove = {};
            for (int y = 0; y < grid.size(); y++) {
                willMove.push_back({});
                for (int x = 0; x < grid[0].size(); x++) {
                    willMove[willMove.size() - 1].push_back(false);
                }
            }

            uint64_t count = 1;
            while (Step(grid, willMove)) {
                count++;
            }

            return count;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto grid = PreProcessInput(input);
            auto count = CountSteps(grid);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { count, endTime - startTime };
        }
    }
}