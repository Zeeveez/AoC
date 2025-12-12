#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day12 : public AoC::Day<std::vector<std::string>, 2025, 12> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::unordered_map<int, std::unordered_set<int>> map;
        std::unordered_map<std::string, int> ids;

        std::vector<std::vector<std::vector<bool>>> baseShapes;
        std::vector<int> baseShapeBits;
        std::vector<std::pair<std::pair<int, int>, std::vector<int>>> boxes;
    };
}