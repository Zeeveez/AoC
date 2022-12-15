#ifndef DAY06_H
#define DAY06_H

#include <vector>
#include <string>
#include <cstdint>
#include <chrono>

namespace AoC2015 {
    namespace Day06 {
        std::vector<uint64_t> CreateLookUpTable(int duration);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input, int duration = 80);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input);
    }
}
#endif