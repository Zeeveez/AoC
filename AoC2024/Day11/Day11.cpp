#include "Day11.h"

#include <optional>
#include <numeric>
#include <unordered_map>

namespace AoC2024 {
    namespace Day11 {
        Stone::Stone(uint64_t value, uint64_t count = 1) {
            this->value = value;
            this->count = count;
        }

        std::optional<Stone> Stone::Iterate() {
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

        uint64_t Run(const std::vector<uint64_t>& input, int iterations) {
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

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<uint64_t>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(input, 25);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<uint64_t>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(input, 75);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}