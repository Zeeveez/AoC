#include <algorithm>
#include <numeric>

#include "Day01.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day01::Parse() {
        rawData = AoC::Helpers::Transpose(rawData);
    }

    AoC::DayResult::PuzzleResult Day01::A() {
        std::sort(rawData[0].begin(), rawData[0].end());
        std::sort(rawData[1].begin(), rawData[1].end());

        uint32_t res = 0;
        for (size_t i = 0; i < rawData[0].size(); i++) {
            res += std::max(rawData[0][i], rawData[1][i]) - std::min(rawData[0][i], rawData[1][i]);
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day01::B() {
        return std::accumulate(
            rawData[0].begin(),
            rawData[0].end(),
            (uint32_t)0,
            [&](uint32_t acc, uint32_t v) {
                return acc + v * std::count(rawData[1].begin(), rawData[1].end(), v);
            }
        );
    }
}