#ifndef DAY02_H
#define DAY02_H

#include <cstdint>
#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day02 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif