#include <cmath>

#include "Day02.h"
#include "../../Helpers/Helpers.h"

namespace AoC2025 {
    void Day02::Parse() {
        input = {};
        bool numFlag = false;
        std::uint64_t num1 = 0;
        std::uint64_t num2 = 0;
        for (auto& c : rawData) {
            if (c == '-') { numFlag = true; }
            else if (c == ',') { input.push_back({ num1, num2 });  numFlag = false; num1 = 0; num2 = 0; }
            else if (!numFlag) { num1 = num1 * 10 + c - '0'; }
            else { num2 = num2 * 10 + c - '0'; }
        }
        input.push_back({ num1, num2 });
    }

    AoC::DayResult::PuzzleResult Day02::A() {
        std::uint64_t res = 0;

        for (auto& pair : input) {
            res += SumInvalid(pair);
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day02::B() {
        std::uint64_t res = 0;

        for (auto& pair : input) {
            res += SumInvalid(pair, true);
        }

        return res;
    }

    std::uint64_t Day02::SumInvalid(const std::pair<std::uint64_t, std::uint64_t>& pair, bool partB) {
        std::uint64_t res = 0;
        std::unordered_set<std::uint64_t> seen = {};

        std::uint64_t lowerBoundDigits = std::log10(pair.first) + 1;
        std::uint64_t upperBoundDigits = std::log10(pair.second) + 1;

        if (partB) {
            for (auto digits = lowerBoundDigits; digits <= upperBoundDigits; digits++) {
                for (auto i = 1; i <= std::pow(10, digits / 2) - 1; i++) {
                    AddIfInvalid(seen, res, pair, i, digits);
                }
            }
        }
        else {
            for (auto digits = lowerBoundDigits; digits <= upperBoundDigits; digits++) {
                if(digits % 2 != 0){ continue; }
                for (auto i = std::pow(10, digits / 2 - 1); i <= std::pow(10, digits / 2) - 1; i++) {
                    AddIfInvalid(seen, res, pair, i, digits);
                }
            }
        }

        return res;
    }

    void Day02::AddIfInvalid(std::unordered_set<std::uint64_t>& seen, std::uint64_t& res, const std::pair<std::uint64_t, std::uint64_t>& range, const std::uint64_t n, const std::uint64_t requiredDigits) {
        std::uint64_t nDigits = std::log10(n) + 1;
        std::uint64_t v = 0;
        while (std::log10(v) + 1 < requiredDigits) {
            v = v * std::pow(10, nDigits) + n;
        }
        if (v >= range.first && v <= range.second && !seen.contains(v)) {
            seen.insert(v);
            res += v;
        }
    }
}