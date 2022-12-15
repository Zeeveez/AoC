#ifndef DAY17_H
#define DAY17_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day17 {
        std::pair<std::pair<int, int>, std::pair<int, int>> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif