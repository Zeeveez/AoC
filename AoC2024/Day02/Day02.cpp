#include "Day02.h"

#include <algorithm>
#include <numeric>

namespace AoC2024 {
    namespace Day02 {
        bool IsSafe(const std::vector<uint64_t>& line, int ignoreIdx) {
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

        uint64_t ProcessA(const std::vector<std::vector<uint64_t>>& input) {
            uint64_t res = 0;
            for (auto& line : input) {
                res += IsSafe(line) ? 1 : 0;
            }
            return res;
        }

        uint64_t ProcessB(const std::vector<std::vector<uint64_t>>& input) {
            uint64_t res = 0;
            for (auto& line : input) {
                for (int i = -1; i < (int)line.size(); i++) {
                    if (IsSafe(line, i)) {
                        res += 1;
                        break;
                    }

                    if (i == line.size() - 1) {
                        int x = 1;
                    }
                }
            }
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