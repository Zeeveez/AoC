#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day13 : public AoC::Day<std::vector<std::string>, 2024, 13> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>> testCases = {};

        uint64_t Solve(const std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>& testCase);
    };
}