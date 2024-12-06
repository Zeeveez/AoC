#include "Day04.h"

namespace AoC2024 {
    namespace Day04 {
        bool Check(const std::vector<std::string>& input, int x, int y, int sx, int sy, std::string target) {
            for (int i = 0; i < target.length(); i++) {
                int cx = x + sx * i;
                int cy = y + sy * i;
                if (cy < 0 || cy >= input.size()) { return false; }
                if (cx < 0 || cx >= input[cy].size()) { return false; }
                if (input[cy][cx] != target[i]) { return false; }
            }
            return true;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
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
                        if (Check(input, x, y, step.first, step.second, "XMAS")) {
                            res++;
                        }
                    }
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

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

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - startTime };
        }
    }
}