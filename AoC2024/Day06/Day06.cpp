#include "Day06.h"

#include <cmath>

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day06::Parse() {
        for (int i = 0; i < rawData.size() + 2; i++) {
            map.push_back('X');
        }
        for (int y = 0; y < rawData.size(); y++) {
            map.push_back('X');
            for (int x = 0; x < rawData[y].size(); x++) {
                map.push_back(rawData[y][x]);
            }
            map.push_back('X');
        }
        for (int i = 0; i < rawData.size() + 2; i++) {
            map.push_back('X');
        }
    }

    AoC::DayResult::PuzzleResult Day06::A() {
        return GetStartAndPath(map).second.size();
    }

    AoC::DayResult::PuzzleResult Day06::B() {
        std::vector<int> loops;
        int size = std::sqrt(map.size());
        loops.resize(size * size * 4, -1);
        auto [startingPos, path] = GetStartAndPath(map);

        std::uint64_t res = 0;
        int iter = 0;
        std::vector<int> dirs = { -1 * size, 1, size, -1 };

        for (auto point : path) {
            if (map[point] == '^' || map[point] == '#') { continue; }

            auto pos = startingPos;
            int dir = 0;

            do {
                short newPos = pos + dirs[dir];
                while (map[newPos] == '#' || newPos == point) {
                    if (loops[pos * 4 + dir] == iter) {
                        res += 1;
                        goto done;
                    }
                    loops[pos * 4 + dir] = iter;
                    dir = (dir + 1) % 4;
                    newPos = pos + dirs[dir];
                }
                pos = newPos;
            } while (map[pos] != 'X');
        done:;
            iter++;
        }

        return res;
    }

    std::pair<int, std::unordered_set<int>> Day06::GetStartAndPath(const std::vector<char>& map) {
        int startingPos = 0;
        for (int i = 0; i < map.size(); i++) {
            if (map[i] == '^') {
                startingPos = i;
                break;
            }
        }
        int pos = startingPos;

        int size = std::sqrt(map.size());
        std::vector<int> dirs = { -size, 1, size, -1 };
        int dir = 0;

        std::unordered_set<int> seen = {};
        do {
            seen.insert(pos);
            int newPos = pos + dirs[dir];
            while (map[newPos] == '#') {
                dir = (dir + 1) % 4;
                newPos = pos + dirs[dir];
            }
            pos += dirs[dir];
        } while (map[pos] != 'X');

        return { startingPos, seen };
    }
}