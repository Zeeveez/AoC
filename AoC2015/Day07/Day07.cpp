#include "Day07.h"

#include <sstream>
#include <algorithm>
#include <limits>
#include <numeric>

namespace AoC2015 {
    namespace Day07 {
        uint64_t Run(const std::vector<int>& input, const std::function<int(int, int)>& accFunc) {
            int maxCrab = *std::max_element(input.begin(), input.end());
            int minCrab = *std::min_element(input.begin(), input.end());

            uint64_t minFuel = std::numeric_limits<uint64_t>::max();
            for (int i = minCrab; i < maxCrab; i++) {
                uint64_t fuel = std::accumulate(input.begin(), input.end(), (uint64_t)0,
                                                [i, &accFunc](uint64_t acc, int crab) {
                                                    return acc + accFunc(i, crab);
                                                });
                minFuel = std::min(fuel, minFuel);
            }
            return minFuel;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto fuelCost = Run(input,
                       [](int i, int crab) {
                           return std::abs(crab - i);
                       });
            auto endTime = std::chrono::high_resolution_clock::now();
            return { fuelCost, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto fuelCost = Run(input,
                       [](int i, int crab) {
                           int n = std::abs(crab - i);
                           return n * (n + 1) / 2;
                       });
            auto endTime = std::chrono::high_resolution_clock::now();
            return { fuelCost, endTime - startTime };
        }
    }
}