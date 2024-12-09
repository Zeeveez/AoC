#include "Day06.h"

namespace AoC2024 {
    namespace Day06 {
        std::vector<char> MakeFlat(const std::vector<std::string>& input) {
            std::vector<char> map = {};
            for (int i = 0; i < input.size() + 2; i++) {
                map.push_back('X');
            }
            for (int y = 0; y < input.size(); y++) {
                map.push_back('X');
                for (int x = 0; x < input[y].size(); x++) {
                    map.push_back(input[y][x]);
                }
                map.push_back('X');
            }
            for (int i = 0; i < input.size() + 2; i++) {
                map.push_back('X');
            }
            return map;
        }

        std::pair<int, std::unordered_set<int>> GetStartAndPath(const std::vector<char>& map) {
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

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = GetStartAndPath(MakeFlat(input)).second.size();

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
            auto map = MakeFlat(input);

            std::vector<int> loops;
            int size = std::sqrt(map.size());
            loops.resize(size * size * 4, -1);
            auto [startingPos, path] = GetStartAndPath(map);

            int res = 0;
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
                    pos += dirs[dir];
                } while (map[pos] != 'X');
            done:;
                iter++;
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}