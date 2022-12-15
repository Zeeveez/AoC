#ifndef DAY15_H
#define DAY15_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day15 {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PreProcessInput(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif