#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day07 : public AoC::Day<std::vector<std::string>, 2024, 7> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<std::vector<uint64_t>> equations = {};

        bool Valid(const std::vector<uint64_t>& eq, bool withConcat = false);
        bool Valid(uint64_t solution, uint64_t current, const std::vector<uint64_t>& eq, int i = 0, bool withConcat = false);
        uint64_t Concat(uint64_t x, uint64_t y);
        uint64_t RunSolution(bool withConcat = false);
    };
}