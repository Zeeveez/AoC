#ifndef DAY23_H
#define DAY23_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <set>

namespace AoC2022 {
    namespace Day23 {
        enum Dir {
            NORTH,
            SOUTH,
            WEST,
            EAST,
            ALL
        };
        std::unordered_map<int, std::set<int>> PreProcessInput(const std::vector<std::string>& input);

        int CountNeighbours(const std::unordered_map<int, std::set<int>>& map, int x, int y, Dir dir = ALL);
        bool Step(std::unordered_map<int, std::set<int>>& map, int cycle);
        int Score(const std::unordered_map<int, std::set<int>>& map);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif