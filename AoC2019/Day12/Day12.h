#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"
#include "Moon/Moon.h"

namespace AoC2019 {
    class Day12 : public AoC::Day<std::vector<std::string>, 2019, 12> {
    private:
        std::vector<std::vector<int>> startingMoons;

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::int64_t gcd(std::int64_t a, std::int64_t b);
        std::int64_t lcm(std::int64_t a, std::int64_t b);
    };
}