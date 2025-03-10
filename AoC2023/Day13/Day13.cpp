#include "Day13.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day13::Load() {
        input = AoC::Helpers::ReadLines("./Day13.txt");
    }

    void Day13::Parse() {
        grids.push_back({});
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
    }

    void Day13::A() {
        uint64_t res = 0;

        for (auto& grid : grids) {
            auto horizReflect = GetHorizontalReflection(grid);
            if (horizReflect != -1) {
                res += horizReflect + 1;
            }
            else {
                auto vertiReflec = GetVerticalReflection(grid);
                res += 100 * (vertiReflec + 1);
            }
        }

        partAResult.first = res;
    }

    void Day13::B() {
        uint64_t res = 0;

        for (auto& grid : grids) {
            auto horizReflect = GetHorizontalReflectionB(grid);
            if (horizReflect != -1) {
                res += horizReflect + 1;
            }
            else {
                auto vertiReflec = GetVerticalReflectionB(grid);
                res += 100 * (vertiReflec + 1);
            }
        }

        partBResult.first = res;
    }



    bool Day13::VerifyHorizontalReflection(const std::vector<std::vector<bool>>& grid, int checkCol, int row) {
        for (int i = 0; i >= -checkCol && checkCol - i + 1 < grid[row].size(); i--) {
            if (grid[row][checkCol + i] != grid[row][checkCol - i + 1]) {
                return false;
            }
        }
        return true;
    }

    int Day13::GetHorizontalReflection(const std::vector<std::vector<bool>>& grid) {
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

    int Day13::GetHorizontalReflectionB(std::vector<std::vector<bool>>& grid) {
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

    bool Day13::VerifyVerticalReflection(const std::vector<std::vector<bool>>& grid, int checkRow, int col) {
        for (int i = 0; i >= -checkRow && checkRow - i + 1 < grid.size(); i--) {
            if (grid[checkRow + i][col] != grid[checkRow - i + 1][col]) {
                return false;
            }
        }
        return true;
    }

    int Day13::GetVerticalReflection(const std::vector<std::vector<bool>>& grid) {
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

    int Day13::GetVerticalReflectionB(std::vector<std::vector<bool>>& grid) {
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
}