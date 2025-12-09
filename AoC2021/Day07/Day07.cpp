#include <cmath>
#include <numeric>

#include "Day07.h"

#include "../../Helpers/Helpers.h"

namespace AoC2021 {
    void Day07::Load() {
        input = AoC::Helpers::ReadCommaDelimitedList("./Day07.txt");
    }

    void Day07::Parse() {
        // No parsing required
    }

    void Day07::A() {
        partAResult.first = Run(
            input,
            [](int i, int crab) {
                return std::abs(crab - i);
            }
        );
    }

    void Day07::B() {
        partBResult.first = Run(
            input,
            [](int i, int crab) {
                int n = std::abs(crab - i);
                return n * (n + 1) / 2;
            }
        );
    }

    uint64_t Day07::Run(const std::vector<int64_t>& input, const std::function<int64_t(int64_t, int64_t)>& accFunc) {
        int64_t maxCrab = *std::max_element(input.begin(), input.end());
        int64_t minCrab = *std::min_element(input.begin(), input.end());

        uint64_t minFuel = std::numeric_limits<uint64_t>::max();
        for (int64_t i = minCrab; i < maxCrab; i++) {
            uint64_t fuel = std::accumulate(input.begin(), input.end(), (uint64_t)0,
                                            [i, &accFunc](uint64_t acc, int64_t crab) {
                                                return acc + accFunc(i, crab);
                                            });
            minFuel = std::min(fuel, minFuel);
        }

        return minFuel;
    }
}