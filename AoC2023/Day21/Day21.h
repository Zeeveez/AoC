#ifndef DAY21_H
#define DAY21_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <set>

namespace AoC2023::Day21 {
    std::pair<int, int> FindStart(const std::vector<std::string>& input);
    std::set<std::pair<int, int>> GetNewPositions(const std::vector<std::string>& input, const std::set<std::pair<int, int>>& currentPositions);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif