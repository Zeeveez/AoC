#ifndef DAY13_H
#define DAY13_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2023::Day13 {
    std::vector<std::vector<std::vector<bool>>> ParseInput(const std::vector<std::string>& input);

    bool VerifyHorizontalReflection(const std::vector<std::vector<bool>>& grid, int checkCol, int row);
    int GetHorizontalReflection(const std::vector<std::vector<bool>>& grid);
    int GetHorizontalReflectionB(std::vector<std::vector<bool>>& grid);

    bool VerifyVerticalReflection(const std::vector<std::vector<bool>>& grid, int checkRow, int col);
    int GetVerticalReflection(const std::vector<std::vector<bool>>& grid);
    int GetVerticalReflectionB(std::vector<std::vector<bool>>& grid);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif