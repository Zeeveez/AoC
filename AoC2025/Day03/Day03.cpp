#include <cstdint>

#include "Day03.h"

namespace AoC2025 {
    AoC::DayResult::PuzzleResult Day03::A() {
        return DoPart(2);
    }

    AoC::DayResult::PuzzleResult Day03::B() {
        return DoPart(12);
    }

    std::uint64_t Day03::DoPart(int digits) {
        std::uint64_t res = 0;

        for (auto& row : rawData) {
            int nextStartI = 0;
            std::uint64_t currentBank = 0;
            for (int p = digits - 1; p > -1; p--) {
                char max = '0';
                for (int i = nextStartI; i < row.size() - p; i++) {
                    if (row[i] > max) { max = row[i]; nextStartI = i + 1; }
                    if (max == '9') { break; }
                }
                currentBank += (max - '0');
                if (p > 0) { currentBank *= 10; }
                max = '0';
            }
            res += currentBank;
        }
        return res;
    }
}