#include "Day22.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day22::Load() {
        input = AoC::Helpers::ReadTokens<int32_t>("./Day22.txt");
    }

    void Day22::Parse() {
        // No parsing required
    }

    uint32_t Step(uint32_t n) {
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

    void Day22::A() {
        uint64_t res = 0;
        for (auto n : input) {
            for (int i = 0; i < 2000; i++) {
                n = Step(n);
            }
            res += n;
        }
        partAResult.first = res;
    }

    void Day22::B() {
        std::vector<int32_t> scores(160000, 0);
        std::vector<int32_t> seenKeys(160000, -1);
        for (int i = 0; i < input.size(); i++) {
            uint32_t n = input[i];
            uint32_t key = 0;
            for (int j = 0; j < 2000; j++) {
                int64_t last = n;
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
        partBResult.first = res;
    }
}