#include "Day03.h"

#include <unordered_map>

namespace AoC2015 {
    namespace Day03 {
        std::unordered_map<size_t, int> Solve(std::string input, std::function<bool(size_t)> indexCheck) {
            size_t x = 100'000;
            size_t y = 100'000;

            std::unordered_map<size_t, int> map = { { x * 200'000 + y, 1 } };

            size_t i = 0;
            for (auto& c : input) {
                if (!indexCheck(i++)) { continue; }
                switch (c) {
                case '>':
                    x++;
                    break;
                case '<':
                    x--;
                    break;
                case 'v':
                    y--;
                    break;
                case '^':
                    y++;
                    break;
                }
                if (!map.contains(x * 200'000 + y)) { map[x * 200'000 + y] = 0; }
                map[x * 200'000 + y]++;
            }

            return map;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(std::string input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto santaMap = Solve(input, [](size_t i) { return true; });

            auto endTime = std::chrono::high_resolution_clock::now();
            return { santaMap.size(), endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(std::string input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto santaMap = Solve(input, [](size_t i) { return i % 2 == 0; });
            auto robotSantaMap = Solve(input, [](size_t i) { return i % 2 == 1; });

            for (auto& kvp : robotSantaMap) {
                if (!santaMap.contains(kvp.first)) { santaMap[kvp.first] = 0; }
                santaMap[kvp.first] += kvp.second;
            }


            auto endTime = std::chrono::high_resolution_clock::now();
            return { santaMap.size(), endTime - startTime };
        }
    }
}