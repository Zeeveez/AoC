#ifndef DAY20_H
#define DAY20_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>

namespace AoC2022 {
    namespace Day20 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input);
    }
}
#endif