#ifndef DAY05_H
#define DAY05_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace AoC2024 {
    namespace Day05 {
        std::tuple<std::unordered_map<int, std::unordered_set<int>>, std::unordered_map<int, std::unordered_set<int>>, std::vector<std::vector<int>>> PreProcess(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif