#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day18 : public AoC::Day<std::vector<std::string>, 2024, 18> {
    private:
        std::vector<std::pair<int, int>> dirs = {
            { 0, 1 },
            { 0, -1 },
            { -1, 0 },
            { 1, 0 },
        };

    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<std::pair<int, int>> coords = {};
        std::vector<int> memory = {};

        uint64_t Simulate(int size, int timePassed);
    };
}