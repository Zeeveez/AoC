#include <cmath>

#include "Day02.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    AoC::DayResult::PuzzleResult Day02::A() {
        uint16_t res = 0;
        for (auto& line : rawData) {
            res += IsSafe(line);
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day02::B() {
        uint16_t res = 0;
        for (auto& line : rawData) {
            for (int i = 0; i < (int)line.size(); i++) {
                if (IsSafe(line, i)) {
                    res++;
                    break;
                }
            }
        }

        return res;
    }

    bool Day02::IsSafe(const std::vector<uint16_t>& line, int ignoreIdx) {
        uint16_t lastVal = line[ignoreIdx == 0];
        int diff = 0;
        for (size_t i = (ignoreIdx == 0) + 1; i < line.size(); i++) {
            if (i == ignoreIdx) { continue; }
            int newDiff = line[i] - lastVal;
            lastVal = line[i];

            if (std::abs(newDiff) == 0 || std::abs(newDiff) > 3) { return false; }
            if (diff != 0 && (diff > 0 && newDiff < 0 || diff < 0 && newDiff > 0)) {
                return false;
            }

            diff = newDiff;
        }
        return true;
    }
}