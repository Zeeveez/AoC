#ifndef DAY11_H
#define DAY11_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <set>

namespace AoC2023::Day11 {
    std::unordered_map<int64_t, std::set<int64_t>> LoadUniverse(const std::vector<std::string>& input);

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif