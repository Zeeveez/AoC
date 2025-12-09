#include "Day06.h"

#include <sstream>
#include <iostream>
#include <numeric>

namespace AoC2021 {
    namespace Day06 {
        std::vector<uint64_t> CreateLookUpTable(int duration) {
            std::vector<uint64_t> fish = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 };
            std::vector<uint64_t> table = {};
            for (int d = 0; d < duration; d++) {
                table.push_back(std::accumulate(fish.begin(), fish.end(), (uint64_t)0));
                for (int i = 0; i <= 9; i++) {
                    if (i == 0) {
                        fish[7] += fish[i];
                        fish[9] += fish[i];
                    }
                    else {
                        fish[i - 1] = fish[i];
                    }
                    fish[i] = 0;
                }
            }
            return table;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int64_t>& input, int duration) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto lookupTable = CreateLookUpTable(duration + 8);
            auto count = std::accumulate(input.begin(), input.end(), (uint64_t)0, [lookupTable, duration](uint64_t acc, int fish) {
                                        return acc + lookupTable[duration + 8 - fish];
                                    });
            auto endTime = std::chrono::high_resolution_clock::now();
            return { count, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int64_t>& input) {
            return A(input, 256);
        }
    }
}