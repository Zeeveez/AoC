#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day10 : public AoC::Day<std::vector<std::string>, 2024, 10> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        int Traverse(const std::vector<std::string>& input, int startX, int startY, bool uniquePeaksOnly = true);
    };
}