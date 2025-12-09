#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day02 : public AoC::Day<std::vector<std::vector<uint16_t>>, 2024, 2> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        bool IsSafe(const std::vector<uint16_t>& line, int ignoreIdx = -1);
    };
}