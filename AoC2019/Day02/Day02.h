#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day02 : public AoC::Day<std::vector<std::int64_t>, 2019, 2> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::int64_t RunProgram(std::vector<std::int64_t> program, std::int64_t noun, std::int64_t verb);
    };
}