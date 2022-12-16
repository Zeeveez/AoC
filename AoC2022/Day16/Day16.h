#ifndef DAY16_H
#define DAY16_H

#include <cstdint>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day16 {
        std::pair<std::unordered_map<int, int>, std::unordered_map<int, std::vector<int>>> PreProcessInput(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif