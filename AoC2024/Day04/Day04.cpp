#include <regex>
#include <numeric>

#include "Day04.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    AoC::DayResult::PuzzleResult Day04::A() {
        std::vector<std::pair<int, int>> steps = {
            { 1, 0 },
            { -1, 0 },
            { 0, 1 },
            { 0, -1 },
            { 1, 1 },
            { -1, 1 },
            { 1, -1 },
            { -1, -1 }
        };

        uint64_t res = 0;
        for (int y = 0; y < rawData.size(); y++) {
            for (int x = 0; x < rawData.size(); x++) {
                for (auto& step : steps) {
                    if (Check(x, y, step.first, step.second, "XMAS")) {
                        res++;
                    }
                }
            }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day04::B() {
        uint64_t res = 0;
        for (int y = 1; y < rawData.size() - 1; y++) {
            for (int x = 1; x < rawData.size() - 1; x++) {
                if (rawData[y][x] != 'A') { continue; }
                int c = 0;
                if (rawData[y - 1][x - 1] == 'M' && rawData[y + 1][x + 1] == 'S') { c++; }
                if (rawData[y - 1][x - 1] == 'S' && rawData[y + 1][x + 1] == 'M') { c++; }
                if (rawData[y - 1][x + 1] == 'M' && rawData[y + 1][x - 1] == 'S') { c++; }
                if (rawData[y - 1][x + 1] == 'S' && rawData[y + 1][x - 1] == 'M') { c++; }
                if (c == 2) {
                    res++;
                }
            }
        }

        return res;
    }


    bool Day04::Check(int x, int y, int sx, int sy, std::string target) {
        for (int i = 0; i < target.length(); i++) {
            int cx = x + sx * i;
            int cy = y + sy * i;
            if (cy < 0 || cy >= rawData.size()) { return false; }
            if (cx < 0 || cx >= rawData[cy].size()) { return false; }
            if (rawData[cy][cx] != target[i]) { return false; }
        }
        return true;
    }
}