#include "Day14.h"

namespace AoC2022 {
    namespace Day14 {
        std::vector<std::vector<std::pair<int, int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<std::pair<int, int>>> data = {};
            for (auto& line : input) {
                data.push_back({});
                for (int i = 0; i < line.length(); i += 3) {
                    int a = 0;
                    int b = 0;
                    while (line[i] != ',') { a = a * 10 + line[i] - '0'; i++; } i++;
                    while (line[i] != ' ' && i < line.length()) { b = b * 10 + line[i] - '0'; i++; } i++;
                    data[data.size() - 1].push_back({ a, b });
                }
            }
            return data;
        }

        void DrawLine(std::vector<std::vector<State>>& grid, std::pair<int, int> p1, std::pair<int, int> p2) {
            auto& [x1, y1] = p1;
            auto& [x2, y2] = p2;

            grid[x1][y1] = State::ROCK;
            for (int x = std::min(x1, x2); x < std::max(x1, x2); x++) {
                grid[x][y1] = State::ROCK;
            }
            for (int y = std::min(y1, y2); y < std::max(y1, y2); y++) {
                grid[x1][y] = State::ROCK;
            }
            grid[x2][y2] = State::ROCK;
        }

        std::vector<std::vector<State>> GenerateGrid(const std::vector<std::vector<std::pair<int, int>>> lines) {
            std::vector<std::vector<State>> grid = {};
            for (int x = 0; x < 1000; x++) {
                grid.push_back({});
                for (int y = 0; y < 1000; y++) { grid[x].push_back(State::AIR); }
            }

            for (auto& line : lines) {
                for (int i = 0; i < line.size() - 1; i++) {
                    DrawLine(grid, line[i], line[i + 1]);
                }
            }

            return grid;
        }

        bool ApplySand(std::vector<std::vector<State>>& grid, int x, int y) {
            while (true) {
                if (y + 1 >= grid[x].size()) {
                    return false;
                }
                if (grid[x][y + 1] == State::AIR) {
                    y++; continue;
                }
                if (grid[x - 1][y + 1] == State::AIR) {
                    x--; y++; continue;
                }
                if (grid[x + 1][y + 1] == State::AIR) {
                    x++; y++; continue;
                }
                if (grid[x - 1][y + 1] != State::AIR && grid[x][y + 1] != State::AIR && grid[x + 1][y + 1] != State::AIR) {
                    grid[x][y] = State::SAND;
                    return true;
                }
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto lines = PreProcessInput(input);
            auto grid = GenerateGrid(lines);

            int res = 0;
            while (true) {
                if (ApplySand(grid, 500, 0)) {
                    res++;
                }
                else {
                    break;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto lines = PreProcessInput(input);
            auto grid = GenerateGrid(lines);
            int maxY = 0;
            for (int x = 0; x < grid.size(); x++) {
                for (int y = 0; y < grid[x].size(); y++) {
                    if (grid[x][y] == State::ROCK) {
                        maxY = std::max(maxY, y);
                    }
                }
            }
            DrawLine(grid, { 0, maxY + 2 }, { grid.size() - 1, maxY + 2 });

            int res = 0;
            while (true) {
                if (ApplySand(grid, 500, 0)) {
                    res++;
                    if (grid[500][0] == State::SAND) {
                        break;
                    }
                }
                else {
                    break;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}