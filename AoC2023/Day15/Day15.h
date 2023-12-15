#ifndef DAY15_H
#define DAY15_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2023::Day15 {
    std::vector<std::string> ParseInput(const std::string& input);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif