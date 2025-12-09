#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day06 : public AoC::Day<std::vector<std::string>, 2025, 6> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::vector<std::vector<char>>> calculations;
    };
}