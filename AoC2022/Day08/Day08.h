#ifndef DAY08_H
#define DAY08_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day08 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input);
        bool IsTreeVisible(const std::vector<std::vector<int>>& grid, int tx, int ty);
        uint64_t GetTreeViewScore(const std::vector<std::vector<int>>& grid, int tx, int ty);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif