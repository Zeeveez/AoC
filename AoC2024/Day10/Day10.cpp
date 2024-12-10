#include "Day10.h"

#include <queue>
#include <unordered_set>

namespace AoC2024 {
    namespace Day10 {
        int Traverse(const std::vector<std::string>& input, int startX, int startY, bool uniquePeaksOnly) {
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

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = 0;
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (input[y][x] == '0') {
                        res += Traverse(input, x, y);
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = 0;
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (input[y][x] == '0') {
                        res += Traverse(input, x, y, false);
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}