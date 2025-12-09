#pragma once
#include <vector>
#include <string>
#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day01 : public AoC::Day<std::vector<std::string>, 2025, 1> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<int> moves;
    };
}