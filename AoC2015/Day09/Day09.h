#ifndef DAY09_H
#define DAY09_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day09 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input);
        int LowPointRiskLevel(const std::vector<std::vector<int>>& grid, int x, int y);
        int FloodFill(std::vector<std::vector<int>>& grid, int x, int y);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif