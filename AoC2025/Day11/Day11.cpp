#include <stack>
#include <ranges>

#include "Day11.h"

namespace AoC2025 {
void Day11::Parse() {
    map = {};
    ids = {};
    for (auto& line : rawData) {
        int src = -1;
        for (auto& rawId : std::ranges::to<std::vector<std::string>>(line | std::views::split(' '))) {
            auto id = rawId.substr(0, 3); // trim :
            if (!ids.contains(id)) { ids[id] = ids.size(); }
            if (src == -1) { src = ids[id]; map[src] = {}; }
            else { map[src].insert(ids[id]); }
        }
    }
}

    AoC::DayResult::PuzzleResult Day11::A() {
        return CountRoutes(ids["you"], ids["out"]);
    }

    AoC::DayResult::PuzzleResult Day11::B() {
        return CountRoutes(ids["svr"], ids["fft"]) * CountRoutes(ids["fft"], ids["dac"]) * CountRoutes(ids["dac"], ids["out"])
            + CountRoutes(ids["svr"], ids["dac"]) * CountRoutes(ids["dac"], ids["fft"]) * CountRoutes(ids["fft"], ids["out"]);
    }

    std::uint64_t Day11::CountRoutes(int from, int to) {
        std::unordered_map<int, int> scores = {};
        CountRoutes(scores, from, to);
        return scores[from];
    }

    std::uint64_t Day11::CountRoutes(std::unordered_map<int, int>& scores, int from, int to) {
        if (scores.contains(from)) { return scores[from]; }
        if (from == to) { return 1; }

        std::uint64_t res = 0;
        for (auto& next : map[from]) {
            res += CountRoutes(scores, next, to);
        }
        scores[from] = res;
        return res;
    }
}