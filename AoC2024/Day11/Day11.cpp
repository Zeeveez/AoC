#include <numeric>
#include <unordered_map>

#include "Day11.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    Day11::Stone::Stone(uint64_t value, uint64_t count = 1) {
        this->value = value;
        this->count = count;
    }

    std::optional<Day11::Stone> Day11::Stone::Iterate() {
        if (value == 0) {
            value = 1;
            return std::nullopt;
        }
        int digits = ((int)std::log10((double)value) + 1);
        if (digits % 2 == 0) {
            Stone newStone = Stone(value % (uint64_t)std::pow(10, digits / 2), count);
            value /= std::pow(10, digits / 2);
            return newStone;
        }
        else {
            value *= 2024;
            return std::nullopt;
        }
    }

    void Day11::Load() {
        input = AoC::Helpers::ReadTokens<uint64_t>("./Day11.txt");
    }

    void Day11::Parse() {
        // No parsing required
    }

    void Day11::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = Run(25);

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day11::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = Run(75);

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }

    uint64_t Day11::Run(int iterations) {
        std::unordered_map<uint64_t, Stone> stones = {};
        for (auto& num : input) {
            stones[num] = Stone(num);
        }

        for (int i = 0; i < iterations; i++) {
            std::vector<Stone> newStones = {};
            for (auto& stone : stones) {
                auto newStone = stone.second.Iterate();
                if (newStone.has_value()) {
                    newStones.push_back(stone.second);
                    newStones.push_back(newStone.value());
                }
                else {
                    newStones.push_back(stone.second);
                }
            }
            stones = {};
            for (auto& stone : newStones) {
                if (stones.contains(stone.value)) {
                    stones[stone.value].count += stone.count;
                }
                else {
                    stones[stone.value] = stone;
                }
            }
        }

        return std::accumulate(
            stones.begin(),
            stones.end(),
            (uint64_t)0,
            [](uint64_t acc, const std::unordered_map<uint64_t, Stone>::value_type& stone) {
                return acc + stone.second.count;
            }
        );
    }
}