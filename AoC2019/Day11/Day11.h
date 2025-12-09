#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day11 : public AoC::Day<std::vector<std::int64_t>, 2019, 11> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;
    };
}