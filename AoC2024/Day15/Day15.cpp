#include "Day15.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day15::Parse() {
        int line = 0;
        while (rawData[line].length()) {
            mapA.push_back({});
            for (auto& c : rawData[line]) {
                if (c == '@') {
                    mapA.back().push_back('.');
                    posA = { mapA.back().size() - 1, mapA.size() - 1 };
                }
                else {
                    mapA.back().push_back(c);
                }
            }

            mapB.push_back({});
            for (auto& c : rawData[line]) {
                switch (c) {
                case '#':
                    mapB.back().push_back('#');
                    mapB.back().push_back('#');
                    break;
                case 'O':
                    mapB.back().push_back('[');
                    mapB.back().push_back(']');
                    break;
                case '.':
                    mapB.back().push_back('.');
                    mapB.back().push_back('.');
                    break;
                case '@':
                    mapB.back().push_back('.');
                    posB = { mapB.back().size() - 1, mapB.size() - 1 };
                    mapB.back().push_back('.');
                    break;
                }
            }
            line++;
        }

        while (line < rawData.size()) {
            moves += rawData[line++];
        }
    }

    AoC::DayResult::PuzzleResult Day15::A() {
        return RunSolution(mapA, posA, MoveA, 'O');
    }

    AoC::DayResult::PuzzleResult Day15::B() {
        return RunSolution(mapB, posB, MoveB, '[');
    }

    bool Day15::MoveA(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool _) {
        if (map[y + dy][x + dx] == '.') { return true; }
        if (map[y + dy][x + dx] == '#') { return false; }
        if (MoveA(map, x + dx, y + dy, dx, dy, _)) {
            map[y + dy * 2][x + dx * 2] = map[y + dy][x + dx];
            map[y + dy][x + dx] = '.';
            return true;
        }
        return false;
    }

    bool Day15::MoveB(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool yMoveTest) {
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

    uint64_t Day15::Score(const std::vector<std::vector<char>>& map, char target) {
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

    uint64_t Day15::RunSolution(
        std::vector<std::vector<char>> map,
        std::pair<int, int> pos,
        std::function<bool(std::vector<std::vector<char>>&, int, int, int, int, bool)> moveFunc,
        char target
    ) {
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
}