#ifndef DAY24_H
#define DAY24_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day24 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif