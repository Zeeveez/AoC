#include "Day03.h"

namespace AoC2019 {
    void Day03::Parse() {
        wire1 = {};
        wire2 = {};

        for (auto i = 0; i < rawData[0].size(); i++) {
            if (rawData[0][i] >= 'A' && rawData[0][i] <= 'Z') {
                wire1.push_back({ rawData[0][i], 0 });
            }
            else if (rawData[0][i] == ',') { continue; }
            else {
                wire1.back().second = wire1.back().second * 10 + rawData[0][i] - '0';
            }
        }

        for (auto i = 0; i < rawData[1].size(); i++) {
            if (rawData[1][i] >= 'A' && rawData[1][i] <= 'Z') {
                wire2.push_back({ rawData[1][i], 0 });
            }
            else if (rawData[1][i] == ',') { continue; }
            else {
                wire2.back().second = wire2.back().second * 10 + rawData[1][i] - '0';
            }
        }
    }

    AoC::DayResult::PuzzleResult Day03::A() {
        std::map<std::pair<int, int>, std::map<int, int>> grid = {};
        RunWire(grid, wire1, 1);
        RunWire(grid, wire2, 2);

        int ret = 9999999;
        for (auto& keyVal : grid) {
            if (keyVal.second.count(1) == 1 && keyVal.second.count(2) == 1) {
                ret = std::min(ret, std::abs(keyVal.first.first) + std::abs(keyVal.first.second));
            }
        }
        return ret;
    }

    AoC::DayResult::PuzzleResult Day03::B() {
        std::map<std::pair<int, int>, std::map<int, int>> grid = {};
        RunWire(grid, wire1, 1);
        RunWire(grid, wire2, 2);

        int ret = 9999999;
        for (auto& keyVal : grid) {
            if (keyVal.second.count(1) == 1 && keyVal.second.count(2) == 1) {
                ret = std::min(ret, keyVal.second[1] + keyVal.second[2]);
            }
        }
        return ret;
    }

    void Day03::RunWire(std::map<std::pair<int, int>, std::map<int, int>>& grid, std::vector<std::pair<char, int>> wire, int wireNo) {
        std::pair<int, int> pos = { 0, 0 };
        int n = 0;
        for (auto& mov : wire) {
            for (int i = 0; i < mov.second; i++) {
                n++;
                switch (mov.first) {
                case 'U':
                    pos.second++;
                    break;
                case 'D':
                    pos.second--;
                    break;
                case 'L':
                    pos.first--;
                    break;
                case 'R':
                    pos.first++;
                    break;
                }
                if (grid.count(pos) == 0) {
                    grid[pos] = { { wireNo, n } };
                }
                else {
                    if (grid[pos].count(wireNo) == 0) {
                        grid[pos][wireNo] = n;
                    }
                }
            }
        }
    }
}