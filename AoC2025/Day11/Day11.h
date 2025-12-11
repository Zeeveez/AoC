#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day11 : public AoC::Day<std::vector<std::string>, 2025, 11> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::unordered_map<int, std::unordered_set<int>> map;
        std::unordered_map<std::string, int> ids;

        int you;
        int out;

        int srv;
        int dac;
        int fft;

        std::uint64_t CountRoutes(int from, int to);
        std::unordered_set<int> NodesReachableFrom(int from);
        void CollapseMap(int from, int newFromLabel);
    };
}