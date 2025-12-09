#pragma once
#include <vector>
#include <string>
#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day01 : public AoC::Day<std::vector<std::uint32_t>, 2019, 1> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;
    };
}