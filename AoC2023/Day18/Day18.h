#ifndef DAY18_H
#define DAY18_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2023::Day18 {
    std::vector<std::tuple<std::pair<int, int>, int, std::pair<int, int>, int>> ParseInput(const std::vector<std::string>& input);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif