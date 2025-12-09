#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day05 : public AoC::Day<std::vector<std::int64_t>, 2019, 5> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::int64_t RunProgram(std::vector<std::int64_t> program, std::int64_t systemID);
    };
}