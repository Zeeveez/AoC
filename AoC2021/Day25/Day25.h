#ifndef DAY25_H
#define DAY25_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day25 {
        std::vector<std::vector<char>> PreProcessInput(const std::vector<std::string>& input);

        bool Step(std::vector<std::vector<char>>& grid, std::vector<std::vector<bool>>& willMove);
        uint64_t CountSteps(std::vector<std::vector<char>>& grid);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    }
}
#endif