#include "Day11.h"

#include <optional>
#include <numeric>

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
            std::vector<Stone> stones = {};
            for (auto& num : input) {
                stones.push_back(Stone(num));
            }

            for (int i = 0; i < iterations; i++) {
                for (int64_t j = stones.size() - 1; j > -1; j--) {
                    auto res = stones[j].Iterate();
                    if (res.has_value()) {
                        stones.insert(stones.begin() + j + 1, res.value());
                    }
                }
                for (int64_t j = stones.size() - 1; j > -1; j--) {
                    for (int64_t k = j - 1; k > -1; k--) {
                        if (stones[j].value == stones[k].value) {
                            stones[k].count += stones[j].count;
                            stones.erase(stones.begin() + j);
                            break;
                        }
                    }
                }
            }

            return std::accumulate(stones.begin(), stones.end(), (uint64_t)0, [](uint64_t acc, const Stone& stone) {return acc + stone.count; });
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