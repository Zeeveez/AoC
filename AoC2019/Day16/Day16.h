#pragma once
#include <vector>
#include <string>
#include <map>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day16 : public AoC::Day<std::string, 2019, 16> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        int GetPatternNumber(long long i, long long n);
        std::string ProcessString(std::string input);
    };
}