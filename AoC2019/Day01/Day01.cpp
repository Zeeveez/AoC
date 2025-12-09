#include <numeric>

#include "Day01.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day01::A() {
        return std::accumulate(rawData.begin(), rawData.end(), 0, [](int acc, int n) { return acc + n / 3 - 2; });
    }

    AoC::DayResult::PuzzleResult Day01::B() {
        int totalFuel = 0;
        for (auto& moduleSize : rawData) {
            int totalModuleFuel = 0;
            while (moduleSize >= 6) {
                moduleSize = moduleSize / 3 - 2;
                totalModuleFuel += moduleSize;
            }
            totalFuel += totalModuleFuel;
        }
        return totalFuel;
    }
}