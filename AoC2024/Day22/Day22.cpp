#include "Day22.h"

#include <unordered_map>
#include <set>
#include <iostream>

namespace AoC2022 {
    namespace Day22 {
        static std::unordered_map<int, std::unordered_map<int, std::unordered_map<char, std::pair<int, int>>>> DIR_CHANGE = {
            {
                0, {
                    { // Facing Up
                        -1, {
                            { 'L', { -1, 0 } },     // Facing Left
                            { 'R', { 1, 0 } },      // Facing Right
                        }
                    },

                    { // Facing Down
                        1, {
                            { 'L', { 1, 0 } },      // Facing Right
                            { 'R', { -1, 0 } },     // Facing Left
                        }
                    },
                }
            },

            {
                1, { // Facing Right
                    {
                        0, {
                            { 'L', { 0, -1 } },     // Facing Up
                            { 'R', { 0, 1 } },      // Facing Down
                        }
                    }
                }
            },


            {
                -1, { // Facing Left
                    {
                        0, {
                            { 'L', { 0, 1 } },      // Facing Down
                            { 'R', { 0, -1 } },     // Facing Up
                        }
                    }
                }
            }
        };

        static std::unordered_map<int, std::unordered_map<int, int>> DIR_SCORE = {
            {
                {
                    0, {
                        { -1, 3 },  // Facing Up
                        { 1, 1 },   // Facing Down
                    }
                },
                {
                    1, {
                        { 0, 0 },   // Facing Right
                    }
                },
                {
                    -1, {
                        { 0, 2 },   // Facing Left
                    }
                }
            }
        };

        std::pair<std::vector<std::vector<State>>, std::vector<Instruction>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<State>> map = {};
            size_t w = 0;
            size_t h = input.size() - 2;
            for (auto& line : input) {
                if (line.length() == 0) { break; }
                w = std::max(w, line.length());
            }

            for (int x = 0; x < w; x++) {
                map.push_back({});
                for (int y = 0; y < h; y++) {
                    if (x < input[y].length()) {
                        switch (input[y][x])
                        {
                        case ' ':
                            map[x].push_back(VOID);
                            break;
                        case '.':
                            map[x].push_back(FLOOR);
                            break;
                        case '#':
                            map[x].push_back(WALL);
                            break;
                        }
                    }
                    else {
                        map[x].push_back(VOID);
                    }
                }
            }

            std::vector<Instruction> instructions = {};
            int steps = 0;
            for (auto& c : input[input.size() - 1]) {
                switch (c) {
                case 'L':
                case 'R':
                    if (steps) {
                        instructions.push_back(Instruction(steps));
                        steps = 0;
                    }
                    instructions.push_back(Instruction(c));
                    break;
                default:
                    steps = steps * 10 + c - '0';
                    break;
                }
            }
            if (steps) {
                instructions.push_back(Instruction(steps));
            }

            return { map, instructions };
        }

        std::pair<int, int> Move(const std::vector<std::vector<State>>& map, std::pair<int, int> pos, std::pair<int, int> dir) {
            auto newPos = pos;
            while (true) {
                // Move
                newPos.first += dir.first;
                newPos.second += dir.second;

                // Wrap
                if (newPos.first < 0) { newPos.first = map.size() - 1; }
                if (newPos.first >= map.size()) { newPos.first = 0; }
                if (newPos.second < 0) { newPos.second = map[newPos.first].size() - 1; }
                if (newPos.second >= map[newPos.first].size()) { newPos.second = 0; }

                // Check
                if (map[newPos.first][newPos.second] == FLOOR) { return newPos; }
                if (map[newPos.first][newPos.second] == WALL) { return pos; }

                // In void; continue
            }
        }

        std::pair<std::pair<int, int>, std::pair<int, int>> CubeMove(const std::vector<std::vector<State>>& map, std::pair<int, int> pos, std::pair<int, int> dir) {
            auto newPos = pos;
            while (true) {
                // Move
                newPos.first += dir.first;
                newPos.second += dir.second;

                // Wrap
                if (newPos.first < 0) { newPos.first = map.size() - 1; }
                if (newPos.first >= map.size()) { newPos.first = 0; }
                if (newPos.second < 0) { newPos.second = map[newPos.first].size() - 1; }
                if (newPos.second >= map[newPos.first].size()) { newPos.second = 0; }

                // Check
                if (map[newPos.first][newPos.second] == FLOOR) { return { newPos, dir }; }
                if (map[newPos.first][newPos.second] == WALL) { return { pos, dir }; }

                // In void; continue
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [map, instructions] = PreProcessInput(input);

            std::pair<int, int> pos = { 0, 0 };
            for (int x = 0; x < map.size(); x++) {
                if (map[x][0] == FLOOR) {
                    pos = { x, 0 };
                    break;
                }
            }
            std::pair<int, int> dir = { 1, 0 };

            std::set<int> visited = { };
            visited.insert(pos.first * 1000 + pos.second);
            for (auto& ins : instructions) {
                if (ins.isMove) {
                    for (int i = 0; i < ins.moveCount; i++) {
                        pos = Move(map, pos, dir);
                        visited.insert(pos.first * 1000 + pos.second);
                    }
                }
                else {
                    dir = DIR_CHANGE[dir.first][dir.second][ins.dir];
                }
            }

            int res = (pos.second + 1) * 1000 + (pos.first + 1) * 4 + DIR_SCORE[dir.first][dir.second];

            //for (int y = 0; y < map[0].size(); y++) {
            //    for (int x = 0; x < map.size(); x++) {
            //        if (visited.contains(x * 1000 + y)) {
            //            std::cout << "+";
            //        }
            //        else {
            //            switch (map[x][y]) {
            //            case WALL:
            //                std::cout << "#";
            //                break;
            //            case FLOOR:
            //                std::cout << ".";
            //                break;
            //            case VOID:
            //                std::cout << " ";
            //                break;
            //            }
            //        }
            //    }
            //    std::cout << "\n";
            //}

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [map, instructions] = PreProcessInput(input);

            std::pair<int, int> pos = { 0, 0 };
            for (int x = 0; x < map.size(); x++) {
                if (map[x][0] == FLOOR) {
                    pos = { x, 0 };
                    break;
                }
            }
            std::pair<int, int> dir = { 1, 0 };

            std::set<int> visited = { };
            visited.insert(pos.first * 1000 + pos.second);
            //for (auto& ins : instructions) {
            //    if (ins.isMove) {
            //        for (int i = 0; i < ins.moveCount; i++) {
            //            auto moveRes = CubeMove(map, pos, dir);
            //            pos = moveRes.first;
            //            dir = moveRes.second;
            //            visited.insert(pos.first * 1000 + pos.second);
            //        }
            //    }
            //    else {
            //        dir = DIR_CHANGE[dir.first][dir.second][ins.dir];
            //    }
            //}

            int res = (pos.second + 1) * 1000 + (pos.first + 1) * 4 + DIR_SCORE[dir.first][dir.second];

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}