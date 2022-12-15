#include "Day02.h"

namespace AoC2021 {
    namespace Day02 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            uint64_t x = 0;
            uint64_t y = 0;
            for (size_t i = 0; i < input.size(); i += 2) {
                switch (input[i][0]) {
                case 'f':
                    x += std::stoull(input[i + 1]);
                    break;
                case 'u':
                    y -= std::stoull(input[i + 1]);
                    break;
                case 'd':
                    y += std::stoull(input[i + 1]);
                    break;
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { x * y, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            uint64_t x = 0;
            uint64_t y = 0;
            int64_t aim = 0;
            for (size_t i = 0; i < input.size(); i += 2) {
                switch (input[i][0]) {
                case 'f':
                    x += std::stoull(input[i + 1]);
                    y += aim * std::stoull(input[i + 1]);
                    break;
                case 'u':
                    aim -= std::stoull(input[i + 1]);
                    break;
                case 'd':
                    aim += std::stoull(input[i + 1]);
                    break;
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { x * y, endTime - startTime };
        }
    }
}