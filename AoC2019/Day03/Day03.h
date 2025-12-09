#pragma once
#include <vector>
#include <string>
#include <map>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day03 : public AoC::Day<std::vector<std::string>, 2019, 3> {
    private:
        std::vector<std::pair<char, int>> wire1;
        std::vector<std::pair<char, int>> wire2;

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        void RunWire(std::map<std::pair<int, int>, std::map<int, int>>& grid, std::vector<std::pair<char, int>> wire, int wireNo);
    };
}