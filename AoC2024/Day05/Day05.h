#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day05 : public AoC::Day<std::vector<std::string>, 2024, 5> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::unordered_map<int, std::unordered_set<int>> whiteList = {};
        std::unordered_map<int, std::unordered_set<int>> blackList = {};
        std::vector<std::vector<int>> updates = {};
    };
}