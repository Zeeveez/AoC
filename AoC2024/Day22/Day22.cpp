#include "Day22.h"
#include "../../Helpers/Helpers.h"

#include <unordered_map>
#include <unordered_set>
#include <ranges>

namespace AoC2024 {
    void Day22::Load() {
        input = AoC::Helpers::ReadTokens<int64_t>("./Day22.txt");
    }

    void Day22::Parse() {
        // No parsing required
    }

    int64_t Step(int64_t n) {
        int64_t n64 = n * 64;
        n ^= n64;
        n %= 16777216;
        int64_t nd32 = n / 32;
        n ^= nd32;
        n %= 16777216;
        int64_t n2048 = n * 2048;
        n ^= n2048;
        n %= 16777216;
        return n;
    }

    void Day22::A() {
        uint64_t res = 0;
        for (auto n : input) {
            for (int i = 0; i < 2000; i++) {
                n = Step(n);
            }
            res += n;
        }
        partAResult.first = res;
    }

    void Day22::B() {
        std::vector<std::vector<std::pair<int, int>>> differences = {};
        for (int i = 0; i < 2000; i++) {
            differences.push_back({});
        }
        for (auto n : input) {
            for (int i = 0; i < 2000; i++) {
                int64_t last = n;
                n = Step(n);
                differences[i].push_back({ n % 10, n % 10 - last % 10 });
            }
        }

        std::unordered_map<int64_t, int64_t> sequenceSums = {};
        for (int i = 0; i < input.size(); i++) {
            std::unordered_set<int64_t> seen = {};
            for (int j = 0; j < 2000 - 4; j++) {
                int64_t key = (differences[j][i].second + 10) * 20 * 20 * 20 + (differences[j + 1][i].second + 10) * 20 * 20 + (differences[j + 2][i].second + 10) * 20 + (differences[j + 3][i].second + 10);

                if (differences[j][i].second == -2 && differences[j + 1][i].second == 1 && differences[j + 2][i].second == -1 && differences[j + 3][i].second == 3) {
                    int x = 0;
                }
                if (!seen.contains(key)) {
                    seen.insert(key);
                    if (!sequenceSums.contains(key)) {
                        sequenceSums[key] = 0;
                    }
                    sequenceSums[key] += differences[j + 3][i].first;
                }
            }
        }

        uint64_t res = *std::ranges::max_element(std::views::values(sequenceSums));
        partBResult.first = res;
    }
}