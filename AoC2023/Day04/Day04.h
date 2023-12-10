#ifndef DAY04_H
#define DAY04_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <set>

namespace AoC2023::Day04 {
    std::pair<std::set<int>, std::set<int>> ParseCard(const std::string& card);
    std::vector<std::pair<std::set<int>, std::set<int>>> ParseInput(const std::vector<std::string>& input);
    size_t GetWins(const std::pair<std::set<int>, std::set<int>>& card);

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif