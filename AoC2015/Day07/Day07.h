#ifndef DAY07_H
#define DAY07_H

#include <vector>
#include <string>
#include <cstdint>
#include <functional>
#include <chrono>

namespace AoC2015 {
    namespace Day07 {
        uint64_t Run(const std::vector<int>& input, const std::function<int(int, int)>& accFunc);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input);
    }
}
#endif