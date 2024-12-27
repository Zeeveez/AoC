#include <algorithm>
#include <numeric>

#include "Day01.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day01::Load() {
        input = AoC::Helpers::ReadTokenGrid<uint32_t>("./Day01.txt");
    }

    void Day01::Parse() {
        input = AoC::Helpers::Transpose(input);
    }

    void Day01::A() {
        std::sort(input[0].begin(), input[0].end());
        std::sort(input[1].begin(), input[1].end());

        uint32_t res = 0;
        for (size_t i = 0; i < input[0].size(); i++) {
            res += std::max(input[0][i], input[1][i]) - std::min(input[0][i], input[1][i]);
        }

        partAResult.first = res;
    }

    void Day01::B() {
        partBResult.first = std::accumulate(
            input[0].begin(),
            input[0].end(),
            (uint32_t)0,
            [&](uint32_t acc, uint32_t v) {
                return acc + v * std::count(input[1].begin(), input[1].end(), v);
            }
        );
    }
}