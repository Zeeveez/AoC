#ifndef DAY14_H
#define DAY14_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day14 {
        enum class State {
            AIR,
            ROCK,
            SAND
        };
        std::vector<std::vector<std::pair<int, int>>> PreProcessInput(const std::vector<std::string>& input);
        void DrawLine(std::vector<std::vector<State>>& grid, std::pair<int, int> p1, std::pair<int, int> p2);
        std::vector<std::vector<State>> GenerateGrid(const std::vector<std::vector<std::pair<int, int>>> lines);
        bool ApplySand(std::vector<std::vector<State>>& grid, int x, int y);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif