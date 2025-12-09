#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day03 : public AoC::Day<std::vector<std::string>, 2025, 3> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::uint64_t DoPart(int digits);
    };
}