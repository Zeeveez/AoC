#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day14 : public AoC::Day<std::vector<std::string>, 2024, 14> {
    private:
        typedef std::pair<int64_t, int64_t> Position;
        typedef std::pair<int64_t, int64_t> Speed;
        typedef std::pair<Position, Speed> Robot;

    public:        
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<Robot> robots = {};
    };
}