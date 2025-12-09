#include <sstream>
#include <numeric>

#include "Day07.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day07::Parse() {
        for (auto& line : rawData) {
            std::vector<uint64_t> eq = {};
            auto s = std::stringstream(line);
            std::string tk;
            while (s >> tk) {
                eq.push_back(std::stoull(tk));
            }
            equations.push_back(eq);
        }
    }

    AoC::DayResult::PuzzleResult Day07::A() {
        return RunSolution();
    }

    AoC::DayResult::PuzzleResult Day07::B() {
        return RunSolution(true);
    }

    bool Day07::Valid(const std::vector<uint64_t>& eq, bool withConcat) {
        return Valid(eq[0], eq[1], eq, 2, withConcat);
    }

    bool Day07::Valid(uint64_t solution, uint64_t current, const std::vector<uint64_t>& eq, int i, bool withConcat) {
        if (eq.size() == i) {
            return solution == current;
        }
        else {
            if (current > solution) { return false; }
            return Valid(solution, current + eq[i], eq, i + 1, withConcat)
                || Valid(solution, current * eq[i], eq, i + 1, withConcat)
                || (withConcat && Valid(solution, Concat(current, eq[i]), eq, i + 1, withConcat));
        }
    }

    uint64_t Day07::Concat(uint64_t x, uint64_t y) {
        uint64_t pow = 10;
        while (y >= pow) { pow *= 10; }
        return x * pow + y;
    }

    uint64_t Day07::RunSolution(bool withConcat) {
        return std::accumulate(
            equations.begin(),
            equations.end(),
            (uint64_t)0,
            [&](const uint64_t acc, const std::vector<uint64_t> eq) {
                return acc + (Valid(eq, withConcat) ? eq[0] : 0);
            }
        );
    }
}