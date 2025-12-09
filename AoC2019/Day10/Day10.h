#pragma once
#include <vector>
#include <string>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day10 : public AoC::Day<std::vector<std::string>, 2019, 10> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::vector<int>> CreateMap(std::vector<std::string> mapData);
        int GreatestCommonFactor(int a, int b);
        std::vector<std::pair<int, int>> GetLineOfSight(std::pair<int, int> station, std::pair<int, int> sight);
        std::vector<std::pair<int, int>> GetVisibleAsteroids(std::pair<int, int> station, std::vector<std::vector<int>>& asteroids);
        std::pair<int, int> GetBestStation(std::vector<std::vector<int>> asteroids);
        double GetAsteroidAngle(std::pair<int, int> station, std::pair<int, int> asteroid);
        void SortByAngle(std::vector<std::pair<std::pair<int, int>, double>>& angles);
    };
}