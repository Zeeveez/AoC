#ifndef DAY20_H
#define DAY20_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day20 {
        std::pair<int, int> FindEnd(const std::vector<std::string>& input);

        uint64_t CountPaths(const std::vector<std::string>& input, std::vector<int>& distancesToEnd, int maxCheatLength, int minTimeSave);
        std::vector<int> GetDistancesFromPoint(const std::vector<std::string>& input, int x, int y);
        uint64_t Run(const std::vector<std::string>& input, int maxCheatLength);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif