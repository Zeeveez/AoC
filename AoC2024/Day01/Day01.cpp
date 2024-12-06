#include "Day01.h"

#include <algorithm>
#include <numeric>

namespace AoC2024 {
    namespace Day01 {
        uint64_t ProcessA(const std::vector<std::vector<uint64_t>>& input) {
            std::vector<uint64_t> col1 = {};
            std::vector<uint64_t> col2 = {};
            for (auto& line : input) {
                col1.push_back(line[0]);
                col2.push_back(line[1]);
            }
            std::sort(col1.begin(), col1.end());
            std::sort(col2.begin(), col2.end());

            uint64_t res = 0;
            for (size_t i = 0; i < col1.size(); i++) {
                res += std::max(col1[i], col2[i]) - std::min(col1[i], col2[i]);
            }

            return res;
        }

        uint64_t ProcessB(const std::vector<std::vector<uint64_t>>& input) {
            std::vector<uint64_t> col1 = {};
            std::vector<uint64_t> col2 = {};
            for (auto& line : input) {
                col1.push_back(line[0]);
                col2.push_back(line[1]);
            }

            uint64_t res = std::accumulate(
                col1.begin(),
                col1.end(),
                (uint64_t)0,
                [&col2](uint64_t acc, uint64_t v) {
                    return acc + v * std::count(col2.begin(), col2.end(), v);
                }
            );
            return res;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::vector<uint64_t>>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto res = ProcessA(input);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::vector<uint64_t>>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto res = ProcessB(input);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { res, endTime - startTime };
        }
    }
}