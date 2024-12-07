#ifndef DAY07_H
#define DAY07_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day07 {
        bool Valid(const std::vector<uint64_t>& eq, bool withConcat = false);
        bool Valid(uint64_t solution, uint64_t current, const std::vector<uint64_t>& eq, int i = 0, bool withConcat = false);
        uint64_t Concat(uint64_t x, uint64_t y);
        uint64_t Run(const std::vector<std::string>& input, bool withConcat = false);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif