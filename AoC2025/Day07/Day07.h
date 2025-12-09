#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_set>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day07 : public AoC::Day<std::vector<std::string>, 2025, 7> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        int beamStart;
        std::vector<std::unordered_set<int>> splitters;
    };
}