#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_set>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day06 : public AoC::Day<std::vector<std::string>, 2024, 6> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<char> map = {};

        std::pair<int, std::unordered_set<int>> GetStartAndPath(const std::vector<char>& map);
    };
}