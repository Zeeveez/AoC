#ifndef DAY01_H
#define DAY01_H

#include <cstdint>
#include <vector>
#include <chrono>

namespace AoC2015 {
    namespace Day01 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input);
    }
}
#endif