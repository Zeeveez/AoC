#ifndef DAY06_H
#define DAY06_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <map>

namespace AoC2023::Day06 {
    std::vector<uint64_t> ParseLine(const std::string& input, bool partB = false);
    std::vector<std::pair<uint64_t, uint64_t>> ParseInput(const std::vector<std::string>& input, bool partB = false);
    uint64_t CountWins(uint64_t time, uint64_t record);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif