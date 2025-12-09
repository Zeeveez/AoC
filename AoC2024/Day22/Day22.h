#pragma once
#include "../../Shared/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day22 : public AoC::Day<std::vector<std::uint32_t>, 2024, 22> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        uint32_t Step(uint32_t n);
    };
}