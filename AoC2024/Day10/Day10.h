#ifndef DAY10_H
#define DAY10_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day10 {
        void HandleCycleA(int64_t& x, int64_t& cycles, int64_t& res);
        void HandleCycleB(int64_t& x, int64_t& cycles, std::vector<std::vector<bool>>& resArray);
        std::pair<int64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif