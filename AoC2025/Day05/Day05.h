#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day05 : public AoC::Day<std::vector<std::string>, 2025, 5> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::pair<std::uint64_t, std::uint64_t>> ranges;
        std::vector<std::uint64_t> ingredients;

        std::vector<std::pair<std::uint64_t, std::uint64_t>> RemoveDuplicateRanges(std::vector<std::pair<std::uint64_t, std::uint64_t>>& ranges);
        void AddRange(std::vector<std::pair<std::uint64_t, std::uint64_t>>& ranges, std::pair<std::uint64_t, std::uint64_t> range);
    };
}