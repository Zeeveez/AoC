#ifndef DAY06_H
#define DAY06_H

#include <cstdint>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day06 {
        size_t Run(const std::string& input, int sequenceLength);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input);
    }
}
#endif