#include "Day15.h"

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

        bool MoveA(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool _) {
            if (map[y + dy][x + dx] == '.') { return true; }
            if (map[y + dy][x + dx] == '#') { return false; }
            if (MoveA(map, x + dx, y + dy, dx, dy, _)) {
                map[y + dy * 2][x + dx * 2] = map[y + dy][x + dx];
                map[y + dy][x + dx] = '.';
                return true;
            }
            return false;
        }

        bool MoveB(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool yMoveTest) {
            if (map[y + dy][x + dx] == '.') { return true; }
            if (map[y + dy][x + dx] == '#') { return false; }
            if (dx) { return MoveA(map, x, y, dx, dy, yMoveTest); }

            int offset = -1 + (map[y + dy][x + dx] == '[') * 2;
            if (MoveB(map, x + dx, y + dy, dx, dy, yMoveTest) && MoveB(map, x + dx + offset, y + dy, dx, dy, yMoveTest)) {
                if (!yMoveTest) {
                    map[y + dy * 2][x + dx * 2] = map[y + dy][x + dx];
                    map[y + dy * 2][x + dx * 2 + offset] = map[y + dy][x + dx + offset];
                    map[y + dy][x + dx] = '.';
                    map[y + dy][x + dx + offset] = '.';
                }
                return true;
            }
            return false;
        }

        uint64_t Score(std::vector<std::vector<char>>& map, char target) {
            uint64_t res = 0;
            for (int y = 0; y < map.size(); y++) {
                for (int x = 0; x < map[y].size(); x++) {
                    if (map[y][x] == target) {
                        res += 100 * y + x;
                    }
                }
            }
            return res;
        }

        uint64_t Run(
            std::function<std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>>(const std::vector<std::string>& input)> parseFunc,
            std::function<bool(std::vector<std::vector<char>>&, int, int, int, int, bool)> moveFunc,
            const std::vector<std::string>& input,
            char target
        ) {
            auto [map, moves, pos] = parseFunc(input);
            auto [x, y] = pos;

            for (auto& move : moves) {
                int dx = move == '<' ? -1 : move == '>' ? 1 : 0;
                int dy = move == '^' ? -1 : move == 'v' ? 1 : 0;
                if (moveFunc(map, x, y, dx, dy, true)) {
                    moveFunc(map, x, y, dx, dy, false);
                }
                if (map[y + dy][x + dx] == '.') { x += dx; y += dy; }
            }

            return Score(map, target);
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(PreProcessInputA, MoveA, input, 'O');

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(PreProcessInputB, MoveB, input, '[');

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}