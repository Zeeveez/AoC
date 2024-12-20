#include <sstream>
#include <set>
#include <queue>
#include <ranges>
#include <algorithm>

#include "Day18.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day18::Load() {
        input = AoC::Helpers::ReadLines("./Day18.txt");
    }

    void Day18::Parse() {
        int size = 71;

        for (auto& line : input) {
            std::stringstream ss(line);
            std::string x;
            std::string y;
            std::getline(ss, x, ',');
            std::getline(ss, y, ',');
            coords.push_back(
                {
                    std::stoi(x),
                    std::stoi(y)
                }
            );
        }

        memory = std::vector<int>(size * size, std::numeric_limits<int>::max());
        for (size_t i = 0; i < coords.size(); i++) {
            memory[coords[i].second * size + coords[i].first] = i;
        }
    }

    void Day18::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        int size = 71;
        size_t timePassed = 1024;
        auto res = Simulate(size, timePassed);

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day18::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        int size = 71;
        size_t timePassed = 1024;

        auto idxSequence = std::views::iota(timePassed, input.size());
        auto v = std::partition_point(idxSequence.begin(), idxSequence.end(), [&](std::size_t i) { return Simulate(size, i) != -1; });

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { input[*v - 1], endTime - startTime };
    }

    uint64_t Day18::Simulate(int size, int timePassed) {
        std::set<std::tuple<int, int>> seen = {};
        std::queue<std::tuple<int, int, int>> queue = {};
        queue.push({ 0,0,0 });
        uint64_t res = 0;

        while (!queue.empty()) {
            auto [x, y, time] = queue.front(); queue.pop();
            if (seen.contains({ x, y })) { continue; }
            seen.insert({ x, y });

            if (x == size - 1 && y == size - 1) {
                return time;
            }

            for (auto& dir : dirs) {
                if (x + dir.first < 0 || x + dir.first >= size || y + dir.second < 0 || y + dir.second >= size) { continue; }
                if (memory[(y + dir.second) * size + x + dir.first] >= timePassed) {
                    queue.push({ x + dir.first, y + dir.second, time + 1 });
                }
            }
        }
        return -1;
    }
}