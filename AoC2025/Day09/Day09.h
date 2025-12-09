#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day09 : public AoC::Day<std::vector<std::string>, 2025, 9> {
    private:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::pair<std::int64_t, std::int64_t>> points;
        bool PointInsideRect(std::pair<std::int64_t, std::int64_t> rectP1, std::pair<std::int64_t, std::int64_t> rectP2, std::pair<std::int64_t, std::int64_t> testPoint);
        bool LineIntersectsRect(std::pair<std::int64_t, std::int64_t> rectP1, std::pair<std::int64_t, std::int64_t> rectP2, std::pair<std::int64_t, std::int64_t> lineP1, std::pair<std::int64_t, std::int64_t> lineP2);
    };
}