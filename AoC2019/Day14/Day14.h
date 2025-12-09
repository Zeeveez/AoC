#pragma once
#include <vector>
#include <string>
#include <map>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day14 : public AoC::Day<std::vector<std::string>, 2019, 14> {
    private:
        std::map<std::string, std::pair<int, std::vector<std::pair<int, std::string>>>> formulae;

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;
    };
}