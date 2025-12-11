#include <stack>

#include "Day11.h"

namespace AoC2025 {
    void Day11::Parse() {
        map = {};
        ids = {};

        for (auto& line : rawData) {
            std::string src = "";
            std::string id = "";
            for (auto& c : line) {
                if (std::isalpha(c)) { id += c; }
                else if (id != "") {
                    if (!ids.contains(id)) { ids[id] = ids.size(); }
                    if (src == "") { src = id; }
                    else {
                        if (!map.contains(ids[src])) { map[ids[src]] = {}; }
                        map[ids[src]].insert(ids[id]);
                    }
                    id = "";
                }
            }
            if (id != "") {
                if (!ids.contains(id)) { ids[id] = ids.size(); }
                if (src == "") { src = id; }
                else {
                    if (!map.contains(ids[src])) { map[ids[src]] = {}; }
                    map[ids[src]].insert(ids[id]);
                }
            }
        }

        you = ids["you"];
        out = ids["out"];
        srv = ids["svr"];
        dac = ids["dac"];
        fft = ids["fft"];
    }

    AoC::DayResult::PuzzleResult Day11::A() {
        return CountRoutes(you, out);
    }

    AoC::DayResult::PuzzleResult Day11::B() {
        return CountRoutes(srv, fft) * CountRoutes(fft, dac) * CountRoutes(dac, out)
            + CountRoutes(srv, dac) * CountRoutes(dac, fft) * CountRoutes(fft, out);
    }

    std::uint64_t Day11::CountRoutes(int from, int to) {
        std::unordered_map<int, int> scores = {};
        CountRoutes(scores, from, to, from);
        return scores[from];
    }

    std::uint64_t Day11::CountRoutes(std::unordered_map<int, int>& scores, int from, int to, int current) {
        if (scores.contains(from)) { return scores[from]; }
        if (current == to) { return 1; }

        std::uint64_t res = 0;
        for (auto& next : map[current]) {
            res += CountRoutes(scores, next, to, next);
        }
        scores[from] = res;
        return res;
    }
}