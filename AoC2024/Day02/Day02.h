#ifndef DAY02_H
#define DAY02_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day02 {
        bool IsSafe(const std::vector<uint64_t>& line, int ignoreIdx = -1);

        uint64_t ProcessA(const std::vector<std::vector<uint64_t>>& input);
        uint64_t ProcessB(const std::vector<std::vector<uint64_t>>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::vector<uint64_t>>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::vector<uint64_t>>& input);
    }
}
#endif