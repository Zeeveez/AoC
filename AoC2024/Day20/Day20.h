#pragma once
#include "../../Shared/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day20 : public AoC::Day<std::vector<std::string>, 2024, 20> {
    public:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::pair<int, int> FindEnd(const std::vector<std::string>& input);

        uint64_t CountPaths(const std::vector<std::string>& input, std::vector<int>& distancesToEnd, int maxCheatLength, int minTimeSave);
        std::vector<int> GetDistancesFromPoint(const std::vector<std::string>& input, int x, int y);
        uint64_t RunSolution(const std::vector<std::string>& input, int maxCheatLength);
    };
}