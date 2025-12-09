#ifndef DAY11_H
#define DAY11_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day11 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input);
        int Step(std::vector<std::vector<int>>& grid);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif