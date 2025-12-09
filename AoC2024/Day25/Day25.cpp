#include "Day25.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day25::Parse() {
        for (int i = 0; i < rawData.size(); i += 8) {
            uint64_t val = 0;
            for (int x = 0; x < 5; x++) {
                val *= 16;
                for (int y = 0; y < 7; y++) {
                    val += rawData[i + y][x] == '#';
                }
            }
            if (rawData[i][0] == '.') {
                keys.push_back(val);
            }
            else {
                locks.push_back(val);
            }
        }
    }

    AoC::DayResult::PuzzleResult Day25::A() {
        uint64_t res = 0;
        for (auto& key : keys) {
            for (auto& lock : locks) {
                if (!((key + lock) & 0b10001000100010001000)) {
                    res++;
                }
            }
        }
        return res;
    }

    AoC::DayResult::PuzzleResult Day25::B() {
        return "Merry Christmas!";
    }
}