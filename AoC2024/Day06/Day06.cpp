#include "Day06.h"

namespace AoC2024 {
    namespace Day06 {
        std::unordered_set<int> GetPath(const std::vector<std::string>& input) {
            std::pair<int, int> pos = { 0, 0 };
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (input[y][x] == '^') {
                        pos = { x, y };
                        y = 1000000;
                        break;
                    }
                }
            }

            std::vector<std::pair<int, int>> dirs = {
                { 0, -1 },
                { 1, 0 },
                { 0, 1 },
                { -1, 0 }
            };
            int dir = 0;

            std::unordered_set<int> seen = {};
            do {
                seen.insert(pos.first * input.size() + pos.second);
                std::pair<int, int> newPos = { pos.first + dirs[dir].first, pos.second + dirs[dir].second };
                while ((newPos.first >= 0 && newPos.first < input[0].size() && newPos.second >= 0 && newPos.second < input.size()) && input[newPos.second][newPos.first] == '#') {
                    dir = (dir + 1) % 4;
                    newPos = { pos.first + dirs[dir].first, pos.second + dirs[dir].second };
                }
                pos.first += dirs[dir].first;
                pos.second += dirs[dir].second;
            } while (pos.first >= 0 && pos.first < input[0].size() && pos.second >= 0 && pos.second < input.size());

            return seen;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto seen = GetPath(input);

            uint64_t res = seen.size();

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            std::pair<int, int> startingPos = { 0, 0 };
            for (int y = 0; y < input.size(); y++) {
                for (int x = 0; x < input[y].size(); x++) {
                    if (input[y][x] == '^') {
                        startingPos = { x, y };
                        y = 1000000;
                        break;
                    }
                }
            }

            auto path = GetPath(input);

            uint64_t res = 0;
            for (auto& point : path) {
                int y = point % input.size();
                int x = point / input.size();
                if (input[y][x] == '^' || input[y][x] == '#') { continue; }

                auto pos = startingPos;
                std::vector<std::pair<int, int>> dirs = {
                    { 0, -1 },
                    { 1, 0 },
                    { 0, 1 },
                    { -1, 0 }
                };
                int dir = 0;
                std::unordered_set<int> seen = {};

                do {
                    if (seen.contains((pos.first * input.size() + pos.second) * 4 + dir)) {
                        res += 1;
                        break;
                    }
                    seen.insert((pos.first * input.size() + pos.second) * 4 + dir);

                    std::pair<int, int> newPos = { pos.first + dirs[dir].first, pos.second + dirs[dir].second };
                    while ((newPos.first >= 0 && newPos.first < input[0].size() && newPos.second >= 0 && newPos.second < input.size()) && (input[newPos.second][newPos.first] == '#' || (newPos.first == x && newPos.second == y))) {
                        dir = (dir + 1) % 4;
                        newPos = { pos.first + dirs[dir].first, pos.second + dirs[dir].second };
                    }
                    pos.first += dirs[dir].first;
                    pos.second += dirs[dir].second;
                } while (pos.first >= 0 && pos.first < input[0].size() && pos.second >= 0 && pos.second < input.size());
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}