#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day06 : public AoC::Day<std::vector<std::string>, 2019, 6> {
    private:
        std::vector<std::tuple<std::string, std::string>> orbits;

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::unordered_map<std::string, std::string> MakeOrbitMap(std::vector<std::tuple<std::string, std::string>>& orbits);
        std::vector<std::string> GetOrbitPath(std::unordered_map<std::string, std::string>& orbitMap, std::string node);
    };
}