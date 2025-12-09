#pragma once
#include "../../Shared/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day21 : public AoC::Day<std::vector<std::string>, 2024, 21> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        uint64_t ShortestSequence(char pos, std::string sequence, int depth, int maxDepth);
    };
}