#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <functional>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day15 : public AoC::Day<std::vector<std::string>, 2024, 15> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<std::vector<char>> mapA = {};
        std::pair<int, int> posA = { 0, 0 };

        std::vector<std::vector<char>> mapB = {};
        std::pair<int, int> posB = { 0, 0 };

        std::string moves = "";

        static bool MoveA(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool _);
        static bool MoveB(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool yMoveTest);

        uint64_t Score(const std::vector<std::vector<char>>& map, char target);

        uint64_t RunSolution(
            std::vector<std::vector<char>> map,
            std::pair<int, int> pos,
            std::function<bool(std::vector<std::vector<char>>&, int, int, int, int, bool)> moveFunc,
            char target
        );
    };
}