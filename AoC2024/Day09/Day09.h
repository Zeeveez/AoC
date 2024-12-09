#ifndef DAY09_H
#define DAY09_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day09 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string input);
    }
}
#endif