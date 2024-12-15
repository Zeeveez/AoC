#include "Day15.h"

#include <iostream>

namespace AoC2024 {
    namespace Day15 {
        std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> PreProcessInputA(const std::vector<std::string>& input) {
            std::vector<std::vector<char>> map = {};
            std::pair<int, int> pos;
            int line = 0;
            while (input[line].length()) {
                map.push_back({});
                for (auto& c : input[line]) {
                    if (c == '@') {
                        map.back().push_back('.');
                        pos = { map.back().size() - 1, map.size() - 1 };
                    }
                    else {
                        map.back().push_back(c);
                    }
                }
                line++;
            }

            std::string moves;
            while (line < input.size()) {
                moves += input[line++];
            }

            return { map, moves, pos };
        }

        std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> PreProcessInputB(const std::vector<std::string>& input) {
            std::vector<std::vector<char>> map = {};
            std::pair<int, int> pos;
            int line = 0;
            while (input[line].length()) {
                map.push_back({});
                for (auto& c : input[line]) {
                    switch (c) {
                    case '#':
                        map.back().push_back('#');
                        map.back().push_back('#');
                        break;
                    case 'O':
                        map.back().push_back('[');
                        map.back().push_back(']');
                        break;
                    case '.':
                        map.back().push_back('.');
                        map.back().push_back('.');
                        break;
                    case '@':
                        map.back().push_back('.');
                        pos = { map.back().size() - 1, map.size() - 1 };
                        map.back().push_back('.');
                        break;
                    }
                }
                line++;
            }

            std::string moves;
            while (line < input.size()) {
                moves += input[line++];
            }

            return { map, moves, pos };
        }

        void MoveA(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int>& pos) {
            int i = 1;
            while (true) {
                if (map[pos.second + dy * i][pos.first + dx * i] == '#') {
                    return;
                }
                if (map[pos.second + dy * i][pos.first + dx * i] == 'O') {
                    i++;
                    continue;
                }

                // found '.'
                for (int j = i; j > 0; j--) {
                    map[pos.second + dy * j][pos.first + dx * j] = 'O';
                }
                map[pos.second + dy][pos.first + dx] = '.';
                pos.first += dx;
                pos.second += dy;
                return;
            }
        }

        bool CanMove(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int> pos) {
            if (map[pos.second + dy][pos.first + dx] == '.') {
                return true;
            }
            if (map[pos.second + dy][pos.first + dx] == '#') {
                return false;
            }

            if (map[pos.second + dy][pos.first + dx] == '[' && dy) {
                return CanMove(map, dx, dy, { pos.first + dx, pos.second + dy })
                    && CanMove(map, dx, dy, { pos.first + dx + 1, pos.second + dy });
            }
            if (map[pos.second + dy][pos.first + dx] == ']' && dy) {
                return CanMove(map, dx, dy, { pos.first + dx, pos.second + dy })
                    && CanMove(map, dx, dy, { pos.first + dx - 1, pos.second + dy });
            }

            for (int i = 1; i < 1000; i++) {
                if (map[pos.second + dy * i][pos.first + dx * i] == '.') {
                    return true;
                }
                if (map[pos.second + dy * i][pos.first + dx * i] != '[' && map[pos.second + dy * i][pos.first + dx * i] != ']') {
                    return false;
                }
            }
        }

        void PushB(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int> pos) {
            if (dx) {
                for (int i = 1; i < 1000; i++) {
                    if (map[pos.second + dy * i][pos.first + dx * i] == '.') {
                        for (int j = i; j > 0; j--) {
                            map[pos.second + dy * j][pos.first + dx * j] = map[pos.second + dy * (j - 1)][pos.first + dx * (j - 1)];
                        }
                        pos.first += dx;
                        pos.second += dy;
                        return;
                    }
                }
            }
            else {
                if (map[pos.second + dy][pos.first + dx] == '[') {
                    if (map[pos.second + dy * 2][pos.first + dx] != '.') {
                        PushB(map, dx, dy, { pos.first + dx, pos.second + dy });
                    }
                    if (map[pos.second + dy * 2][pos.first + dx + 1] != '.') {
                        PushB(map, dx, dy, { pos.first + dx + 1, pos.second + dy });
                    }
                    map[pos.second + dy * 2][pos.first + dx] = '[';
                    map[pos.second + dy * 2][pos.first + dx + 1] = ']';
                    map[pos.second + dy][pos.first + dx] = '.';
                    map[pos.second + dy][pos.first + dx + 1] = '.';
                }
                if (map[pos.second + dy][pos.first + dx] == ']') {
                    if (map[pos.second + dy * 2][pos.first + dx] != '.') {
                        PushB(map, dx, dy, { pos.first + dx, pos.second + dy });
                    }
                    if (map[pos.second + dy * 2][pos.first + dx - 1] != '.') {
                        PushB(map, dx, dy, { pos.first + dx - 1, pos.second + dy });
                    }
                    map[pos.second + dy * 2][pos.first + dx] = ']';
                    map[pos.second + dy * 2][pos.first + dx - 1] = '[';
                    map[pos.second + dy][pos.first + dx] = '.';
                    map[pos.second + dy][pos.first + dx -1] = '.';
                }
            }

        }

        void MoveB(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int>& pos) {
            if (CanMove(map, dx, dy, pos)) {
                PushB(map, dx, dy, pos);
                pos.first += dx;
                pos.second += dy;
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [map, moves, pos] = PreProcessInputA(input);
            for (auto& move : moves) {
                switch (move) {
                case '^':
                    MoveA(map, 0, -1, pos);
                    break;
                case '>':
                    MoveA(map, 1, 0, pos);
                    break;
                case 'v':
                    MoveA(map, 0, 1, pos);
                    break;
                case '<':
                    MoveA(map, -1, 0, pos);
                    break;
                }
            }

            uint64_t res = 0;
            for (int y = 0; y < map.size(); y++) {
                for (int x = 0; x < map[y].size(); x++) {
                    if (map[y][x] == 'O') {
                        res += 100 * y + x;
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [map, moves, pos] = PreProcessInputB(input);
            for (auto& move : moves) {
                switch (move) {
                case '^':
                    MoveB(map, 0, -1, pos);
                    break;
                case '>':
                    MoveB(map, 1, 0, pos);
                    break;
                case 'v':
                    MoveB(map, 0, 1, pos);
                    break;
                case '<':
                    MoveB(map, -1, 0, pos);
                    break;
                }
            }

            uint64_t res = 0;
            for (int y = 0; y < map.size(); y++) {
                for (int x = 0; x < map[y].size(); x++) {
                    if (map[y][x] == '[') {
                        res += 100 * y + x;
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}