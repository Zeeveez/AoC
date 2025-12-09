#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day04 : public AoC::Day<std::vector<std::string>, 2024, 4> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        bool Check(int x, int y, int sx, int sy, std::string target);
    };
}