#ifndef DAY13_H
#define DAY13_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2023::Day13 {
    std::vector<std::vector<std::vector<bool>>> ParseInput(const std::vector<std::string>& input);

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif