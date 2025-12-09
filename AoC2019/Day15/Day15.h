#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    class Day15 : public AoC::Day<std::vector<std::int64_t>, 2019, 15> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::pair<std::int64_t, std::int64_t> FindUnsearched(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& mazeMap);
        void TraversePath(IntCodeCPU& computer, std::int64_t& x, std::int64_t& y, std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& arena, std::vector<std::pair<std::int64_t, std::int64_t>> path);
        std::vector<std::pair<std::int64_t, std::int64_t>> GetPath(std::int64_t x, std::int64_t y, std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& arena, std::pair<std::int64_t, std::int64_t> destination);
        bool SearchMaze(IntCodeCPU& computer, std::int64_t& x, std::int64_t& y, std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& arena);
        std::pair<std::int64_t, std::int64_t> FindStart(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> mazeMap);
        std::pair<std::int64_t, std::int64_t> FindEnd(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> mazeMap);
        std::vector<std::vector<std::int64_t>> MapToMaze(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> mazeMap);
        void FloodFill(std::vector<std::vector<std::int64_t>>& maze, std::pair<std::int64_t, std::int64_t> origin, int n = 0);
    };
}