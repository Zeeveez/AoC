#include "Day07.h"

namespace AoC2024 {
    namespace Day07 {
        bool Valid(uint64_t solution, uint64_t current, const std::vector<uint64_t>& eq, int i, bool withConcat) {
            if (eq.size() == i) {
                return solution == current;
            }
            else {
                return Valid(solution, current + eq[i], eq, i + 1, withConcat)
                    || Valid(solution, current * eq[i], eq, i + 1, withConcat)
                    || (withConcat && Valid(solution, Concat(current, eq[i]), eq, i + 1, withConcat));
            }
        }

        uint64_t Concat(uint64_t x, uint64_t y) {
            uint64_t pow = 10;
            while (y >= pow){ pow *= 10; }
            return x * pow + y;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::vector<uint64_t>>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = 0;
            for (auto& line : input) {
                if (Valid(line[0], line[1], line, 2)) {
                    res += line[0];
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::vector<uint64_t>>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t res = 0;
            for (auto& line : input) {
                if (Valid(line[0], line[1], line, 2, true)) {
                    res += line[0];
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - startTime };
        }
    }
}