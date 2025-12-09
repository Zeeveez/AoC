#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <set>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day12 : public AoC::Day<std::vector<std::string>, 2024, 12> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::set<std::pair<int, int>> GetShape(int x, int y, std::set<std::pair<int, int>>& seen);
    };
}