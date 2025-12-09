#ifndef DAY23_H
#define DAY23_H

#include <vector>
#include <string>
#include <tuple>
#include <chrono>

namespace AoC2015 {
    namespace Day23 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input);
        void AddPartB(std::vector<std::string>& input);

        std::vector<std::tuple<std::pair<int, int>, int, uint64_t>> GetMoves(const std::vector<std::vector<int>>& currentRooms, const std::vector<int>& hallway);

        uint64_t Solve(std::vector<std::vector<int>>& currentRooms, std::vector<int>& hallway, int depth = 0);
        uint64_t Solve(std::vector<std::vector<int>>& currentRooms);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif