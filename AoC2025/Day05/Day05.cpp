#include <cctype>

#include "Day05.h"

namespace AoC2025 {
    void Day05::Parse() {
        ranges = {};
        ingredients = {};

        for (auto& line : rawData) {
            if (line == "") { continue; }
            std::uint64_t v = 0;
            for (auto& c : line) {
                if (std::isdigit(c)) { v = v * 10 + c - '0'; }
                else if (c == '-') {
                    ranges.push_back({ v,0 });
                    v = 0;
                }
            }
            if (ranges.size() && ranges.back().second == 0) {
                ranges.back().second = v;
            }
            else {
                ingredients.push_back(v);
            }
        }
    }

    AoC::DayResult::PuzzleResult Day05::A() {
        std::uint64_t res = 0;

        for (auto& ingredient : ingredients) {
            for (auto& range : ranges) {
                if (ingredient >= range.first && ingredient <= range.second) {
                    res++;
                    break;
                }
            }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day05::B() {
        std::uint64_t res = 0;

        for (auto& range : RemoveDuplicateRanges(ranges)) {
            res += range.second - range.first + 1;
        }

        return res;
    }

    std::vector<std::pair<std::uint64_t, std::uint64_t>> Day05::RemoveDuplicateRanges(std::vector<std::pair<std::uint64_t, std::uint64_t>>& ranges) {
        std::vector<std::pair<std::uint64_t, std::uint64_t>> newRanges = {};
        for (auto& range : ranges) {
            AddRange(newRanges, range);
        }
        return newRanges;
    }

    void Day05::AddRange(std::vector<std::pair<std::uint64_t, std::uint64_t>>& ranges, std::pair<std::uint64_t, std::uint64_t> range) {
        for (auto& oldRange : ranges) {
            if (range.second < oldRange.first) { continue; }
            if (range.first > oldRange.second) { continue; }

            if (range.first < oldRange.first && range.second >= oldRange.first) {
                // overlaps at front; split at boundary
                AddRange(ranges, { range.first, oldRange.first - 1 });
                AddRange(ranges, { oldRange.first, range.second });
                return;
            }
            if (range.first <= oldRange.second && range.second > oldRange.second) {
                // overlaps at end; split at boundary
                AddRange(ranges, { range.first, oldRange.second });
                AddRange(ranges, { oldRange.second + 1, range.second });
                return;
            }
            // ranges overlap entirely
            return;
        }
        // No overlap
        ranges.push_back(range);
    }
}