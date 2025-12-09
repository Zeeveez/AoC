#pragma once
#include <cstdint>
#include <optional>
#include <vector>
#include <string>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day11 : public AoC::Day<std::vector<std::uint64_t>, 2024, 11> {
    private:
        class Stone {
        public:
            uint64_t value;
            uint64_t count;
            Stone() = default;
            Stone(uint64_t value, uint64_t count);
            std::optional<Stone> Iterate();
        };

    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        uint64_t RunSolution(int iterations);
    };
}