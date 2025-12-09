#include "Day01.h"

namespace AoC2021 {
    namespace Day01 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input, size_t compareOffset) {
            auto startTime = std::chrono::high_resolution_clock::now();
            uint64_t c = 0;
            for (auto i = compareOffset; i < input.size(); i++) {
                if (input[i] > input[i - compareOffset]) {
                    c++;
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input) {
            return A(input, 3);
        }
    }
}