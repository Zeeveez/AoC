#include <chrono>
#include <algorithm>
#include <numeric>

#include "Day01.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day01::Load() {
        input = AoC::Helpers::ReadTokenGrid<uint64_t>("./Day01.txt");
    }

    void Day01::Parse() {
        // No parsing required
    }

    void Day01::A() {
        auto starttime = std::chrono::high_resolution_clock::now();

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

        auto endtime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endtime - starttime };
    }

    void Day01::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

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

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }
}