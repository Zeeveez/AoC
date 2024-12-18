#ifndef DAY12_H
#define DAY12_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day12 {
        int Traverse(const std::vector<std::string>& input, int startX, int startY, bool uniquePeaksOnly = true);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif