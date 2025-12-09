#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day04 : public AoC::Day<std::vector<std::string>, 2025, 4> {
    private:
        enum class State {
            DEAD,
            WILL_DIE,
            ALIVE
        };
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::vector<State>> input;
    };
}