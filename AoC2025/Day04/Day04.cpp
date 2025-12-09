#include <cstdint>

#include "Day04.h"

namespace AoC2025 {
    void Day04::Parse() {
        input = {};
        for (int y = 0; y < rawData.size(); y++) {
            input.push_back({});
            for (int x = 0; x < rawData.size(); x++) {
                input.back().push_back(rawData[y][x] == '@' ? State::ALIVE : State::DEAD);
            }
        }
    }

    AoC::DayResult::PuzzleResult Day04::A() {
        std::uint64_t res = 0;
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input.size(); x++) {
                if (input[y][x] == State::DEAD) { continue; }

                int c = 0;
                for (int dy = -1; dy < 2; dy++) {
                    for (int dx = -1; dx < 2; dx++) {
                        if (y + dy < 0 || y + dy >= input.size()) { continue; }
                        if (x + dx < 0 || x + dx >= input.size()) { continue; }
                        if (input[y + dy][x + dx] == State::ALIVE) { c++; }
                    }
                }

                if (c <= 4) {   // <= 4 as the current tile is also counted
                    res++;
                }
            }
        }
        return res;
    }

    AoC::DayResult::PuzzleResult Day04::B() {
        std::uint64_t res = 0;
        std::uint64_t iterRes = 0;
        auto activeData = input;
        do {
            iterRes = 0;

            for (int y = 0; y < activeData.size(); y++) {
                for (int x = 0; x < activeData.size(); x++) {
                    if (activeData[y][x] == State::DEAD) { continue; }

                    int c = 0;
                    for (int dy = -1; dy < 2; dy++) {
                        for (int dx = -1; dx < 2; dx++) {
                            if (y + dy < 0 || y + dy >= activeData.size()) { continue; }
                            if (x + dx < 0 || x + dx >= activeData.size()) { continue; }
                            if (activeData[y + dy][x + dx] != State::DEAD) { c++; }
                        }
                    }

                    if (c <= 4) {   // <= 4 as the current tile is also counted
                        iterRes++;
                        activeData[y][x] = State::WILL_DIE;
                    }
                }
            }

            for (int y = 0; y < activeData.size(); y++) {
                for (int x = 0; x < activeData.size(); x++) {
                    if (activeData[y][x] == State::WILL_DIE) { activeData[y][x] = State::DEAD; }
                }
            }

            res += iterRes;
        } while (iterRes);
        return res;
    }
}