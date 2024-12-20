#include <cmath>

#include "Day02.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day02::Load() {
        input = AoC::Helpers::ReadTokenGrid<uint64_t>("./Day02.txt");
    }

    void Day02::Parse() {
        // No parsing required
    }

    void Day02::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = 0;
        for (auto& line : input) {
            res += IsSafe(line) ? 1 : 0;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day02::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = 0;
        for (auto& line : input) {
            for (int i = -1; i < (int)line.size(); i++) {
                if (IsSafe(line, i)) {
                    res += 1;
                    break;
                }
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }

    bool Day02::IsSafe(const std::vector<uint64_t>& line, int ignoreIdx) {
        uint64_t lastVal = ignoreIdx == 0 ? line[1] : line[0];
        int diff = 0;
        for (size_t i = ignoreIdx == 0 ? 2 : 1; i < line.size(); i++) {
            if (i == ignoreIdx) { continue; }
            int newDiff = line[i] - lastVal;
            lastVal = line[i];

            if (std::abs(newDiff) == 0 || std::abs(newDiff) > 3) { return false; }
            if (diff != 0 && (diff > 0 && newDiff < 0 || diff < 0 && newDiff > 0)) {
                return false;
            }

            diff = newDiff;
        }
        return true;
    }
}