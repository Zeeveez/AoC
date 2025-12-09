#pragma once
#include "../../Shared/Day/Day.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace AoC2024 {
    class Day23 : public AoC::Day<std::vector<std::string>, 2024, 23> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::unordered_map<int, std::unordered_set<int>> map = {};
        std::string IDToString(int id);
    };
}