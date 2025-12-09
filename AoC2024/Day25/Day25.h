#pragma once
#include "../../Shared/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day25 : public AoC::Day<std::vector<std::string>, 2024, 25> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<uint64_t> keys = {};
        std::vector<uint64_t> locks = {};
    };
}