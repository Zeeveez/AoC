#include <regex>
#include <numeric>

#include "Day04.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day04::Load() {
        input = AoC::Helpers::ReadLines("./Day04.txt");
    }

    void Day04::Parse() {
        // No parsing required
    }

    void Day04::A() {
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
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input.size(); x++) {
                for (auto& step : steps) {
                    if (Check(x, y, step.first, step.second, "XMAS")) {
                        res++;
                    }
                }
            }
        }

        partAResult.first = res;
    }

    void Day04::B() {
        uint64_t res = 0;
        for (int y = 1; y < input.size() - 1; y++) {
            for (int x = 1; x < input.size() - 1; x++) {
                if (input[y][x] != 'A') { continue; }
                int c = 0;
                if (input[y - 1][x - 1] == 'M' && input[y + 1][x + 1] == 'S') { c++; }
                if (input[y - 1][x - 1] == 'S' && input[y + 1][x + 1] == 'M') { c++; }
                if (input[y - 1][x + 1] == 'M' && input[y + 1][x - 1] == 'S') { c++; }
                if (input[y - 1][x + 1] == 'S' && input[y + 1][x - 1] == 'M') { c++; }
                if (c == 2) {
                    res++;
                }
            }
        }

        partBResult.first = res;
    }


    bool Day04::Check(int x, int y, int sx, int sy, std::string target) {
        for (int i = 0; i < target.length(); i++) {
            int cx = x + sx * i;
            int cy = y + sy * i;
            if (cy < 0 || cy >= input.size()) { return false; }
            if (cx < 0 || cx >= input[cy].size()) { return false; }
            if (input[cy][cx] != target[i]) { return false; }
        }
        return true;
    }
}