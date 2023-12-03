#ifndef DAY01_H
#define DAY01_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2023 {
    namespace Day01 {
        std::vector<uint64_t> GetDigits(const std::string& input, bool includeWords = false);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif