#include "Day22.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    uint32_t Day22::Step(uint32_t n) {
        uint32_t n64 = n << 6;
        n ^= n64;
        n &= 0xffffff;
        uint32_t nd32 = n >> 5;
        n ^= nd32;
        n &= 0xffffff;
        uint32_t n2048 = n << 11;
        n ^= n2048;
        n &= 0xffffff;
        return n;
    }

    AoC::DayResult::PuzzleResult Day22::A() {
        uint64_t res = 0;
        for (auto n : rawData) {
            for (int i = 0; i < 2000; i++) {
                n = Step(n);
            }
            res += n;
        }
        return res;
    }

    AoC::DayResult::PuzzleResult Day22::B() {
        std::vector<uint32_t> scores(160000, 0);
        std::vector<int> seenKeys(160000, -1);
        for (int i = 0; i < rawData.size(); i++) {
            uint32_t n = rawData[i];
            uint32_t key = 0;
            for (int j = 0; j < 2000; j++) {
                uint32_t last = n;
                n = Step(n);
                key = key % 8000 * 20 + n % 10 - last % 10 + 10;
                if (j > 3) {
                    if (seenKeys[key] < i) {
                        seenKeys[key] = i;
                        scores[key] += n % 10;
                    }
                }
            }
        }

        uint64_t res = *std::max_element(scores.begin(), scores.end());
        return res;
    }
}