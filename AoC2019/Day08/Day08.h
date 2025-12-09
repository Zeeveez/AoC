#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day08 : public AoC::Day<std::string, 2019, 8> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::vector<std::vector<int>>> CreateImage(std::string imgData, int width, int height);
        std::vector<std::vector<int>> FlattenLayers(std::vector<std::vector<std::vector<int>>> img);
    };
}