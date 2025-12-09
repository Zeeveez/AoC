#include <numeric>
#include <algorithm>

#include "Day12.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day12::Load() {
        input = AoC::Helpers::ReadLines("./Day12.txt");
    }

    void Day12::Parse() {
        // No parsing required
    }

    void Day12::A() {
        partAResult.first = Solve();
    }

    void Day12::B() {
        partBResult.first = Solve(true);
    }

    uint64_t Day12::Solve(bool partB) {
        std::vector<SpringRow> springs;
        springs.reserve(input.size());
        std::transform(input.begin(), input.end(), std::back_inserter(springs), [partB](const std::string& line) { return SpringRow(line, partB); });

        return std::accumulate(
            springs.begin(),
            springs.end(),
            (uint64_t)0,
            [](uint64_t acc, SpringRow& s) {
                return acc + s.CountPossibilities();
            }
        );
    }

    Day12::SpringRow::SpringRow(const std::string& input, bool partB) {
        auto baseSprings = input.substr(0, input.find(' '));
        auto baseCounts = input.substr(input.find(' ') + 1);

        std::string extendedSprings = "";
        std::string counts = "";

        for (size_t i = 0; i < (partB ? 5 : 1); i++) {
            extendedSprings += (i ? "?" : "") + baseSprings;
            counts += (i ? "," : "") + baseCounts;
        }
        counts += ",";

        damagedSpringGroups = {};

        for (auto& c : extendedSprings) {
            if (c == '.' && springs.length() && springs.back() == '.') {
                continue;
            }
            springs += c;
        }

        int v = 0;
        for (auto& c : counts) {
            if (c >= '0' && c <= '9') {
                v = v * 10 + c - '0';
            }
            else {
                damagedSpringGroups.push_back(v);
                v = 0;
            }
        }

        cache.resize((springs.length() + 2) * (damagedSpringGroups.size() + 1));
        std::ranges::fill(cache, std::numeric_limits<size_t>::max());
    }

    size_t Day12::SpringRow::CountPossibilities(size_t pos, size_t currentGroupIdx, size_t toFit) {
        // Memoization
        size_t idx = pos * (damagedSpringGroups.size() + 1) + currentGroupIdx;
        if (cache[idx] != std::numeric_limits<size_t>::max()) {
            // nothing to do here
        }

        // Captured all groups, check if valid
        else if (currentGroupIdx == damagedSpringGroups.size()) {
            cache[idx] =
                pos <= springs.size() &&
                std::ranges::contains(
                    std::ranges::subrange(
                        std::next(std::begin(springs), pos),
                        std::end(springs)
                    ),
                    '#'
                )
                ? 0
                : 1;
        }

        // No way to fit groups
        else if (springs.size() - pos < toFit) {
            cache[idx] = 0;
        }

        // Skip gaps
        else if (springs[pos] == '.') {
            cache[idx] = CountPossibilities(pos + 1, currentGroupIdx, toFit);
        }

        // Forced group position
        else if (springs[pos] == '#') {
            // Spring group doesn't end at expected position
            if (springs[pos + damagedSpringGroups[currentGroupIdx]] == '#') {
                cache[idx] = 0;
            }
            else {
                cache[idx] =
                    !std::ranges::contains(
                        std::ranges::subrange(
                            std::next(std::begin(springs), pos),
                            std::next(std::begin(springs), pos + damagedSpringGroups[currentGroupIdx])
                        ),
                        '.'
                    )
                    ? CountPossibilities(pos + damagedSpringGroups[currentGroupIdx] + 1, currentGroupIdx + 1, toFit - damagedSpringGroups[currentGroupIdx] - 1)
                    : 0;
            }
        }
        else {
            size_t res = 0;

            // Try #
            res +=
                springs[pos + damagedSpringGroups[currentGroupIdx]] != '#'
                &&
                !std::ranges::contains(
                    std::ranges::subrange(
                        std::next(std::begin(springs), pos + 1),
                        std::next(std::begin(springs), pos + damagedSpringGroups[currentGroupIdx])
                    ),
                    '.'
                )
                ? CountPossibilities(pos + damagedSpringGroups[currentGroupIdx] + 1, currentGroupIdx + 1, toFit - damagedSpringGroups[currentGroupIdx] - 1)
                : 0;

            // Try .
            res += CountPossibilities(pos + 1, currentGroupIdx, toFit);

            cache[idx] = res;
        }

        return cache[idx];
    }

    size_t Day12::SpringRow::CountPossibilities() {
        size_t toFit = std::accumulate(damagedSpringGroups.begin(), damagedSpringGroups.end(), 0) + damagedSpringGroups.size() - 1;
        return CountPossibilities(0, 0, toFit);
    }
}