#include <cmath>

#include "Day01.h"

namespace AoC2025 {
    void Day01::Parse() {
        moves = {};
        for (auto& line : rawData) {
            auto n = 0;
            for (int i = 1; i < line.length(); i++) {
                n = n * 10 + line[i] - '0';
            }
            if (line[0] == 'L') { n *= -1; }
            moves.push_back(n);
        }
    }

    AoC::DayResult::PuzzleResult Day01::A() {
        std::uint64_t res = 0;

        int pos = 50;
        for (auto& move : moves) {
            pos = (pos + move + 10000) % 100;
            if (pos == 0) { res++; }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day01::B() {
        std::uint64_t res = 0;

        int pos = 50;
        for (auto& move : moves) {
            auto hundreds = std::abs(move) / 100;
            res += hundreds;
            auto remaining = move - (move / 100) * 100;

            auto prevPos = pos;
            pos += remaining;

            if (prevPos > 0 && pos <= 0) { res++; }
            else if (pos >= 100) { res++; }
            pos = (pos + 1000) % 100;
        }

        return res;
    }
}