#ifndef DAY25_H
#define DAY25_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day25 {
        uint64_t SNAFUToInt(std::string snafu);
        std::string IntToSNAFU(uint64_t v);
        std::pair<std::string, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif