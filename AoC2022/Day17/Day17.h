#ifndef DAY17_H
#define DAY17_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day17 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif