#include <numeric>
#include <queue>

#include "Day11.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day11::Load() {
        input = AoC::Helpers::ReadLines("./Day11.txt");
    }

    void Day11::Parse() {
        for (int64_t y = 0; y < input.size(); y++) {
            for (int64_t x = 0; x < input[y].size(); x++) {
                if (input[y][x] != '#') { continue; }
                if (!universe.contains(x)) { universe[x] = {}; }
                universe[x].insert(y);
            }
        }
    }

    void Day11::A() {
        partAResult.first = Solve(1);
    }

    void Day11::B() {
        partBResult.first = Solve(999999);;
    }

    uint64_t Day11::Solve(int64_t expansionAmount) {
        auto expansions = GetExpansionsPerDimension(input[0].size(), input.size());

        uint64_t score = 0;
        std::set<std::pair<int64_t, int64_t>> measuredFrom = {};
        for (auto& [x1, stars1] : universe) {
            for (auto& y1 : stars1) {
                measuredFrom.insert({ x1, y1 });
                for (auto& [x2, stars2] : universe) {
                    for (auto& y2 : stars2) {
                        if (measuredFrom.contains({ x2, y2 })) {
                            continue;
                        }

                        score += std::abs(x1 + expansions.first[x1] * expansionAmount - x2 - expansions.first[x2] * expansionAmount)
                            + std::abs(y1 + expansions.second[y1] * expansionAmount - y2 - expansions.second[y2] * expansionAmount);
                    }
                }
            }
        }

        return score;
    }

    std::pair<std::vector<int64_t>, std::vector<int64_t>> Day11::GetExpansionsPerDimension(int64_t width, int64_t height) {
        std::vector<int64_t> widthExpansions = { 0 };
        for (int64_t x = 0; x < width - 1; x++) {
            widthExpansions.push_back(widthExpansions.back() + (universe.contains(x) ? 0 : 1));
        }

        std::vector<int64_t> heightExpansions = { 0 };
        for (int64_t y = 0; y < height - 1; y++) {
            bool empty = true;
            for (const auto& row : universe) {
                if (row.second.contains(y)) {
                    empty = false;
                    break;
                }
            }
            heightExpansions.push_back(heightExpansions.back() + (empty ? 1 : 0));
        }

        return { widthExpansions, heightExpansions };
    }
}