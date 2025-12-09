#include "Day23.h"

#include <iostream>

namespace AoC2022 {
    namespace Day23 {
        std::unordered_map<int, std::vector<std::pair<int, int>>> neighbours = {
            { NORTH, { { -1, -1 }, { 0, -1 }, { 1, -1 } } },
            { SOUTH, { { -1, 1 }, { 0, 1 }, { 1, 1 } } },
            { WEST, { { -1, -1 }, { -1, 0 }, { -1, 1 } } },
            { EAST, { { 1, -1 }, { 1, 0 }, { 1, 1 } } },
            { ALL, { { -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 } } }
        };

        std::unordered_map<int, std::pair<int, int>> moveDirections = {
            { NORTH, { 0, -1 } },
            { SOUTH, { 0, 1 } },
            { WEST, { -1, 0 } },
            { EAST, { 1, 0 } }
        };

        std::vector<std::vector<Dir>> priorities = {
            { NORTH, SOUTH, WEST, EAST },
            { SOUTH, WEST, EAST, NORTH },
            { WEST, EAST, NORTH, SOUTH },
            { EAST, NORTH, SOUTH, WEST }
        };

        std::unordered_map<int, std::set<int>> PreProcessInput(const std::vector<std::string>& input) {
            std::unordered_map<int, std::set<int>> map = {};
            for (int x = 0; x < input[0].size(); x++) {
                for (int y = 0; y < input.size(); y++) {
                    if (input[y][x] == '#') {
                        if (!map.contains(x)) { map.insert({ x, {} }); }
                        map[x].insert(y);
                    }
                }
            }
            return map;
        }

        int CountNeighbours(const std::unordered_map<int, std::set<int>>& map, int x, int y, Dir dir) {
            int c = 0;
            for (auto& neighbour : neighbours.at(dir)) {
                if (map.contains(x + neighbour.first) && map.at(x + neighbour.first).contains(y + neighbour.second)) {
                    c++;
                }
            }
            return c;
        }

        bool Step(std::unordered_map<int, std::set<int>>& map, int cycle) {
            auto& moveList = priorities[cycle % priorities.size()];

            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> moves = {};
            for (auto& row : map) {
                auto x = row.first;
                for (auto& y : map.at(x)) {
                    if (!CountNeighbours(map, x, y)) { continue; }
                    for (auto& move : moveList) {
                        if (CountNeighbours(map, x, y, move)) { continue; }
                        moves.push_back({ { x, y }, { x + moveDirections[move].first, y + moveDirections[move].second } });
                        break;
                    }
                }
            }

            bool moveMade = false;
            for (int i = 0; i < moves.size(); i++) {
                bool valid = true;
                for (int j = 0; j < moves.size(); j++) {
                    if (i == j) { continue; }
                    if (moves[i].second.first == moves[j].second.first
                        && moves[i].second.second == moves[j].second.second) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    moveMade = true;
                    map[moves[i].first.first].erase(moves[i].first.second);

                    if (!map.contains(moves[i].second.first)) { map.insert({ moves[i].second.first, {} }); }
                    map[moves[i].second.first].insert(moves[i].second.second);
                }
            }

            return moveMade;
        }

        int Score(const std::unordered_map<int, std::set<int>>& map) {
            int minX = 999999;
            int maxX = -999999;
            int minY = 999999;
            int maxY = -999999;
            for (auto& col : map) {
                minX = std::min(minX, col.first);
                maxX = std::max(maxX, col.first);
                for (auto& cell : col.second) {
                    minY = std::min(minY, cell);
                    maxY = std::max(maxY, cell);
                }
            }

            int tiles = 0;
            int elves = 0;
            for (int y = minY; y <= maxY; y++) {
                for (int x = minX; x <= maxX; x++) {
                    tiles++;
                    if (map.contains(x) && map.at(x).contains(y)) {
                        elves++;
                    }
                }
            }

            return tiles - elves;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto map = PreProcessInput(input);

            for (int i = 0; i < 10; i++) {
                Step(map, i);
            }

            int res = Score(map);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto map = PreProcessInput(input);

            int res = 0;
            while (Step(map, res++)) { }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}