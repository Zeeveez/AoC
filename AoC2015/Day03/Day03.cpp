#include <regex>
#include <numeric>

#include "Day03.h"

#include "../../Helpers/Helpers.h"

namespace AoC2015 {
    void Day03::Load() {
        input = AoC::Helpers::ReadToken<std::string>("./Day03.txt");
    }

    void Day03::Parse() {
        // No parsing required
    }

    void Day03::A() {
        partAResult.first = Solve(input, [](size_t i) { return true; }).size();
    }

    void Day03::B() {
        auto santaMap = Solve(input, [](size_t i) { return i % 2 == 0; });
        auto robotSantaMap = Solve(input, [](size_t i) { return i % 2 == 1; });

        for (auto& kvp : robotSantaMap) {
            if (!santaMap.contains(kvp.first)) { santaMap[kvp.first] = 0; }
            santaMap[kvp.first] += kvp.second;
        }

        partBResult.first = santaMap.size();
    }

    std::unordered_map<size_t, int> Day03::Solve(std::string input, std::function<bool(size_t)> indexCheck) {
        size_t x = 100'000;
        size_t y = 100'000;

        std::unordered_map<size_t, int> map = { { x * 200'000 + y, 1 } };

        size_t i = 0;
        for (auto& c : input) {
            if (!indexCheck(i++)) { continue; }
            switch (c) {
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
            case 'v':
                y--;
                break;
            case '^':
                y++;
                break;
            }
            if (!map.contains(x * 200'000 + y)) { map[x * 200'000 + y] = 0; }
            map[x * 200'000 + y]++;
        }

        return map;
    }
}