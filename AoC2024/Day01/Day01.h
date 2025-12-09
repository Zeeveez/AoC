#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day01 : public AoC::Day<std::vector<std::vector<uint32_t>>, 2024, 1> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;
    };
}