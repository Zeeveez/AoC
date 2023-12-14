#include "Day13.h"

#include <iostream>
#include <numeric>

namespace AoC2023::Day13 {
    std::vector<std::vector<std::vector<bool>>> ParseInput(const std::vector<std::string>& input) {
        std::vector<std::vector<std::vector<bool>>> grids = { { } };
        for (auto& line : input) {
            if (line == "") {
                grids.push_back({});
                continue;
            }
            grids.back().push_back({});
            for (auto& c : line) {
                grids.back().back().push_back(c == '#');
            }
        }
        return grids;
    }

    bool VerifyHorizontalReflection(const std::vector<std::vector<bool>>& grid, int checkCol, int row) {
        for (int i = 0; i >= -checkCol && checkCol - i + 1 < grid[row].size(); i--) {
            if (grid[row][checkCol + i] != grid[row][checkCol - i + 1]) {
                return false;
            }
        }
        return true;
    }

    int GetHorizontalReflection(const std::vector<std::vector<bool>>& grid) {
        for (int checkCol = 0; checkCol < grid[0].size() - 1; checkCol++) {
            for (size_t i = 0; i < grid.size(); i++) {
                if (!VerifyHorizontalReflection(grid, checkCol, i)) {
                    goto checkNextCol;
                }
            }
            return checkCol;

        checkNextCol:;
        }
        return -1;
    }

    int GetHorizontalReflectionB(std::vector<std::vector<bool>>& grid) {
        auto firstHorizReflection = GetHorizontalReflection(grid);
        for (int checkCol = 0; checkCol < grid[0].size() - 1; checkCol++) {
            if (checkCol == firstHorizReflection) { continue; }

            for (size_t y = 0; y < grid.size(); y++) {
                for (size_t x = 0; x < grid[y].size(); x++) {
                    grid[y][x] = !grid[y][x];
                    for (size_t i = 0; i < grid.size(); i++) {
                        if (!VerifyHorizontalReflection(grid, checkCol, i)) {
                            goto checkNextColB;
                        }
                    }
                    return checkCol;
                checkNextColB:;
                    grid[y][x] = !grid[y][x];
                }
            }

        }
        return -1;
    }

    bool VerifyVerticalReflection(const std::vector<std::vector<bool>>& grid, int checkRow, int col) {
        for (int i = 0; i >= -checkRow && checkRow - i + 1 < grid.size(); i--) {
            if (grid[checkRow + i][col] != grid[checkRow - i + 1][col]) {
                return false;
            }
        }
        return true;
    }

    int GetVerticalReflection(const std::vector<std::vector<bool>>& grid) {
        for (int checkRow = 0; checkRow < grid.size() - 1; checkRow++) {
            for (size_t i = 0; i < grid[0].size(); i++) {
                if (!VerifyVerticalReflection(grid, checkRow, i)) {
                    goto checkNextRow;
                }
            }
            return checkRow;

        checkNextRow:;
        }
        return -1;
    }

    int GetVerticalReflectionB(std::vector<std::vector<bool>>& grid) {
        auto firstVertiReflection = GetVerticalReflection(grid);
        for (int checkRow = 0; checkRow < grid.size() - 1; checkRow++) {
            if (checkRow == firstVertiReflection) { continue; }

            for (size_t y = 0; y < grid.size(); y++) {
                for (size_t x = 0; x < grid[y].size(); x++) {
                    grid[y][x] = !grid[y][x];
                    for (size_t i = 0; i < grid[0].size(); i++) {
                        if (!VerifyVerticalReflection(grid, checkRow, i)) {
                            goto checkNextRowB;
                        }
                    }
                    return checkRow;
                checkNextRowB:;
                    grid[y][x] = !grid[y][x];
                }
            }

        checkNextRow:;
        }
        return -1;
    }


    std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto starttime = std::chrono::high_resolution_clock::now();

        auto grids = ParseInput(input);

        uint64_t score = 0;

        for (auto& grid : grids) {
            auto horizReflect = GetHorizontalReflection(grid);
            if (horizReflect != -1) {
                score += horizReflect + 1;
            }
            else {
                auto vertiReflec = GetVerticalReflection(grid);
                score += 100 * (vertiReflec + 1);
            }
        }

        auto endtime = std::chrono::high_resolution_clock::now();
        return { score, endtime - starttime };
    }

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto starttime = std::chrono::high_resolution_clock::now();

        auto grids = ParseInput(input);

        uint64_t score = 0;

        for (auto& grid : grids) {
            auto horizReflect = GetHorizontalReflectionB(grid);
            if (horizReflect != -1) {
                score += horizReflect + 1;
            }
            else {
                auto vertiReflec = GetVerticalReflectionB(grid);
                score += 100 * (vertiReflec + 1);
            }
        }

        auto endtime = std::chrono::high_resolution_clock::now();
        return { score, endtime - starttime };
    }
}