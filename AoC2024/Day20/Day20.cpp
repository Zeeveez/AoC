#include <queue>

#include "Day20.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    std::vector<std::pair<int, int>> dirs = {
        { 0, 1 },
        { 0, -1 },
        { -1, 0 },
        { 1, 0 },
    };

    AoC::DayResult::PuzzleResult Day20::A() {
        return RunSolution(rawData, 2);
    }

    AoC::DayResult::PuzzleResult Day20::B() {
        return RunSolution(rawData, 20);
    }

    std::pair<int, int> Day20::FindEnd(const std::vector<std::string>& input) {
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[0].size(); x++) {
                if (input[y][x] == 'E') {
                    return { x, y };
                }
            }
        }
    }

    uint64_t Day20::CountPaths(const std::vector<std::string>& input, std::vector<int>& distancesToEnd, int maxCheatLength, int minTimeSave) {
        uint64_t res = 0;
        int size = input.size();
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                int tileIdx = y * size + x;

                // Start not on path
                if (distancesToEnd[tileIdx] == std::numeric_limits<int>::max()) { continue; }

                for (int dy = std::max(-maxCheatLength, -y); dy <= maxCheatLength; dy++) {
                    if (y + dy >= size) { break; }
                    for (int dx = std::max(-(maxCheatLength - std::abs(dy)), -x); dx <= maxCheatLength - std::abs(dy); dx++) {
                        if (x + dx >= size) { break; }
                        int targetTileIdx = (y + dy) * size + x + dx;

                        // Target not on path
                        if (distancesToEnd[targetTileIdx] == std::numeric_limits<int>::max()) { continue; }

                        if (distancesToEnd[targetTileIdx] > distancesToEnd[tileIdx]) { continue; }
                        if (std::abs(distancesToEnd[tileIdx] - distancesToEnd[targetTileIdx]) - (std::abs(dy) + std::abs(dx)) < minTimeSave) { continue; }
                        res++;
                    }
                }
            }
        }
        return res;
    }

    std::vector<int> Day20::GetDistancesFromPoint(const std::vector<std::string>& input, int x, int y) {
        std::vector<int> distances(input.size() * input.size(), std::numeric_limits<int>::max());
        std::queue<std::tuple<int, int, int>> queue = {};
        queue.push({ x, y, 0 });

        while (!queue.empty()) {
            auto [x, y, steps] = queue.front(); queue.pop();
            if (distances[y * input.size() + x] != std::numeric_limits<int>::max()) { continue; }
            distances[y * input.size() + x] = steps;

            for (auto& [dx, dy] : dirs) {
                if (input[y + dy][x + dx] == '#') { continue; }
                queue.push({ x + dx, y + dy, steps + 1 });
            }
        }
        return distances;
    }

    uint64_t Day20::RunSolution(const std::vector<std::string>& input, int maxCheatLength) {
        const int MIN_TIME_SAVE = 100;
        auto end = FindEnd(input);
        auto distancesToEnd = GetDistancesFromPoint(input, end.first, end.second);
        return CountPaths(input, distancesToEnd, maxCheatLength, MIN_TIME_SAVE);
    }
}