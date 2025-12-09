#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day03 : public AoC::Day<std::vector<std::string>, 2024, 3> {
    private:
        enum class Instruction {
            MUL,
            DO,
            DONT
        };
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<std::tuple<Instruction, int, int>> instructions = {};
    };
}