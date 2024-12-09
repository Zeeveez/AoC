#ifndef DAY06_H
#define DAY06_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_set>

namespace AoC2024 {
    namespace Day06 {
        std::vector<char> MakeFlat(const std::vector<std::string>& input);
        std::unordered_set<int> GetPath(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif