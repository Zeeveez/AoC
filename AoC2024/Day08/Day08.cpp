#include <numeric>

#include "Day08.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day08::Load() {
        input = AoC::Helpers::ReadLines("./Day08.txt");
    }

    void Day08::Parse() {
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[y].size(); x++) {
                if (input[y][x] != '.') {
                    if (!nodes.contains(input[y][x])) {
                        nodes[input[y][x]] = {};
                    }
                    nodes[input[y][x]].push_back({ x, y });
                }
            }
        }
    }

    void Day08::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = Run(AddAntinodesA);

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day08::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = Run(AddAntinodesB);

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }

    void Day08::AddAntinodesA(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid) {
        int dx = a.first - b.first;
        int dy = a.second - b.second;
        int newx1 = a.first + dx;
        int newy1 = a.second + dy;
        int newx2 = b.first - dx;
        int newy2 = b.second - dy;

        if (newy1 >= 0 && newy1 < grid.size() && newx1 >= 0 && newx1 < grid[newy1].size()) {
            grid[newy1][newx1] = '#';
        }
        if (newy2 >= 0 && newy2 < grid.size() && newx2 >= 0 && newx2 < grid[newy2].size()) {
            grid[newy2][newx2] = '#';
        }
    }

    void Day08::AddAntinodesB(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid) {
        int dx = a.first - b.first;
        int dy = a.second - b.second;
        int newx1 = a.first;
        int newy1 = a.second;
        int newx2 = b.first;
        int newy2 = b.second;

        while (newy1 >= 0 && newy1 < grid.size() && newx1 >= 0 && newx1 < grid[newy1].size()) {
            grid[newy1][newx1] = '#';
            newx1 -= dx;
            newy1 -= dy;
        }
        while (newy2 >= 0 && newy2 < grid.size() && newx2 >= 0 && newx2 < grid[newy2].size()) {
            grid[newy2][newx2] = '#';
            newx2 += dx;
            newy2 += dy;
        }
    }

    uint64_t Day08::CountAntinodes(const std::vector<std::string>& grid) {
        uint64_t res = 0;
        return std::accumulate(
            grid.begin(),
            grid.end(),
            0ull,
            [](uint64_t acc, const std::string& line) {
                return acc + std::accumulate(
                    line.begin(),
                    line.end(),
                    0ull,
                    [](uint64_t acc, char c) {
                        return acc + (c == '#' ? 1 : 0);
                    }
                );
            }
        );
    }

    uint64_t Day08::Run(std::function<void(const std::pair<int, int>&, const std::pair<int, int>&, std::vector<std::string>&)> antinodeFunc) {
        auto grid = input;
        for (auto& kvp : nodes) {
            for (const auto& n1 : kvp.second) {
                for (const auto& n2 : kvp.second) {
                    if (n1 == n2) { continue; }
                    antinodeFunc(n1, n2, grid);
                }
            }
        }
        return CountAntinodes(grid);
    }
}