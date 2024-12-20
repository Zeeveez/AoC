#include <queue>
#include <unordered_set>

#include "Day10.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day10::Load() {
        input = AoC::Helpers::ReadLines("./Day10.txt");
    }

    void Day10::Parse() {
        // No parsing required
    }

    void Day10::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = 0;
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                if (input[y][x] == '0') {
                    res += Traverse(input, x, y);
                }
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day10::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = 0;
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                if (input[y][x] == '0') {
                    res += Traverse(input, x, y, false);
                }
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }

    int Day10::Traverse(const std::vector<std::string>& input, int startX, int startY, bool uniquePeaksOnly) {
        std::unordered_set<int> seen = {};
        int res = 0;
        std::queue<std::pair<int, int>> queue = {};
        queue.push({ startX, startY });

        while (!queue.empty()) {
            auto [x, y] = queue.front(); queue.pop();
            if (uniquePeaksOnly) {
                if (seen.contains(y * input.size() + x)) {
                    continue;
                }
                seen.insert(y * input.size() + x);
            }
            if (input[y][x] == '9') {
                res++;
                continue;
            }
            if (x > 0 && input[y][x - 1] == input[y][x] + 1) {
                queue.push({ x - 1, y });
            }
            if (y > 0 && input[y - 1][x] == input[y][x] + 1) {
                queue.push({ x, y - 1 });
            }
            if (x < input[y].size() - 1 && input[y][x + 1] == input[y][x] + 1) {
                queue.push({ x + 1, y });
            }
            if (y < input.size() - 1 && input[y + 1][x] == input[y][x] + 1) {
                queue.push({ x, y + 1 });
            }
        }

        return res;
    }
}