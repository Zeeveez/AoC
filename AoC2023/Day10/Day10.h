#ifndef DAY10_H
#define DAY10_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <functional>
#include <set>

namespace AoC2023::Day10 {
    enum class Pipe {
        UP_DOWN,
        LEFT_RIGHT,
        UP_RIGHT,
        UP_LEFT,
        DOWN_LEFT,
        DOWN_RIGHT,
        GROUND,
        START
    };

    std::vector<Pipe> ParseLine(const std::string& input);
    std::vector<std::vector<Pipe>> ParseGrid(const std::vector<std::string>& input);

    std::pair<size_t, size_t> FindStart(const std::vector<std::vector<Pipe>>& grid);

    std::vector<std::pair<size_t, size_t>> GetPathNeighbours(const std::vector<std::vector<Pipe>>& grid, const std::pair<size_t, size_t>& pos);
    std::vector<std::pair<size_t, size_t>> GetAllNeighbours(const std::vector<std::vector<int>>& grid, const std::pair<size_t, size_t>& pos);

    std::set<std::pair<size_t, size_t>> FindPath(const std::vector<std::vector<Pipe>>& grid, const std::pair<size_t, size_t>& pos);
    uint64_t FindVolume(const std::vector<std::vector<Pipe>>& grid, const std::set<std::pair<size_t, size_t>>& path);

    std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif