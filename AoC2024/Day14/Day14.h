#ifndef DAY14_H
#define DAY14_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day14 {
        typedef std::pair<int64_t, int64_t> Position;
        typedef std::pair<int64_t, int64_t> Speed;
        typedef std::pair<Position, Speed> Robot;
        std::vector<Robot> PreProcessInput(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif