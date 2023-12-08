#ifndef DAY08_H
#define DAY08_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>

namespace AoC2023 {
    namespace Day08 {
        std::unordered_map<int, std::pair<int, int>> LoadPaths(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif