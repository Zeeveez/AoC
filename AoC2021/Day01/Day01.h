#ifndef DAY01_H
#define DAY01_H

#include <cstdint>
#include <vector>
#include <chrono>

namespace AoC2021 {
    namespace Day01 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input, size_t compareOffset = 1);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input);
    }
}
#endif