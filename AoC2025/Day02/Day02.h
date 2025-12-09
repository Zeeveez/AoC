#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <tuple>
#include <unordered_set>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day02 : public AoC::Day<std::string, 2025, 2> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::pair<std::uint64_t, std::uint64_t>> input;
        std::uint64_t SumInvalid(const std::pair<std::uint64_t, std::uint64_t>& pair, bool partB = false);
        void AddIfInvalid(std::unordered_set<std::uint64_t>& seen, std::uint64_t& res, const std::pair<std::uint64_t, std::uint64_t>& range, const std::uint64_t n, const std::uint64_t requiredDigits);
    };
}