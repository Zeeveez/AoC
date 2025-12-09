#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day13 : public AoC::Day<std::vector<std::int64_t>, 2019, 13> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;
    };
}