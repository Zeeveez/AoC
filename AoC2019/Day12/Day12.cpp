#include <numeric>
#include <unordered_set>

#include "Day12.h"

namespace AoC2019 {
    void Day12::Parse() {
        startingMoons = {};
        for (auto& line : rawData) {
            startingMoons.push_back({});
            bool negative = false;
            int v = 0;

            for (auto& c : line) {
                if (c == ',' || c == '>') {
                    startingMoons.back().push_back(v * (negative ? -1 : 1));
                    negative = false;
                    v = 0;
                }
                else if (c >= '0' && c <= '9') {
                    v = v * 10 + c - '0';
                }
                else if (c == '-') {
                    negative = true;
                }
            }
        }
    }

    AoC::DayResult::PuzzleResult Day12::A() {
        std::vector<Moon> moons = {};
        for (auto& moon : startingMoons) {
            moons.push_back(Moon(moon[0], moon[1], moon[2]));
        }

        for (int i = 0; i < 1000; i++) {
            for (size_t m = 0; m < moons.size(); m++) {
                for (size_t om = m + 1; om < moons.size(); om++) {
                    moons[m].UpdateVel(moons[om]);
                }
            }
            for (size_t m = 0; m < moons.size(); m++) {
                moons[m].Move();
            }
        }

        return std::accumulate(moons.begin(), moons.end(), 0, [](int acc, Moon moon) {return acc + moon.GetEnergy(); });
    }

    AoC::DayResult::PuzzleResult Day12::B() {
        std::vector<Moon> moons = {};
        for (auto& moon : startingMoons) {
            moons.push_back(Moon(moon[0], moon[1], moon[2]));
        }

        std::int64_t ticks = 0;
        std::vector<std::int64_t> periods = { -1,-1,-1 };
        do {
            ticks++;
            for (size_t m = 0; m < moons.size(); m++) {
                for (size_t om = m + 1; om < moons.size(); om++) {
                    moons[m].UpdateVel(moons[om]);
                }
            }
            for (size_t m = 0; m < moons.size(); m++) {
                moons[m].Move();
            }
            for (int i = 0; i < 3; i++) {
                if (periods[i] == -1) {
                    if (moons[0].AtStart(i) && moons[1].AtStart(i) && moons[2].AtStart(i) && moons[3].AtStart(i)) {
                        periods[i] = ticks;
                    }
                }
            }
        } while (periods[0] == -1 || periods[1] == -1 || periods[2] == -1);
        return lcm(periods[0], lcm(periods[1], periods[2]));
    }

    std::int64_t Day12::gcd(std::int64_t a, std::int64_t b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    std::int64_t Day12::lcm(std::int64_t a, std::int64_t b) {
        return std::abs(a * b) / gcd(a, b);
    }
}