#include <numeric>
#include <map>

#include "Day14.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day14::Load() {
        input = AoC::Helpers::ReadLines("./Day14.txt");
    }

    void Day14::Parse() {
        // No parsing required
    }

    void Day14::A() {
        auto grid = MakeGrid();
        Tilt(grid, { 0, -1 });

        uint64_t res = 0;
        for (size_t i = 0; i < grid.size(); i++) {
            for (auto& cell : grid[i]) {
                if (cell == Tile::ROUND) {
                    res += grid.size() - i;
                }
            }
        }
        partAResult.first = res;
    }

    void Day14::B() {
        auto grid = MakeGrid();
        std::map<std::vector<std::vector<Tile>>, size_t> seen = {};

        size_t cycleStart = 0;
        size_t cycleEnd = 0;
        for (size_t i = 0; i < 1000000000; i++) {
            Cycle(grid);

            if (seen.contains(grid)) {
                cycleStart = seen[grid];
                cycleEnd = i;
                break;
            }
            else {
                seen.insert({ grid, i });
            }
        }

        size_t fixCycles = (1000000000 - cycleStart) % (cycleEnd - cycleStart) - 1;
        for (size_t i = 0; i < fixCycles; i++) {
            Cycle(grid);
        }

        uint64_t res = 0;
        for (size_t i = 0; i < grid.size(); i++) {
            for (auto& cell : grid[i]) {
                if (cell == Tile::ROUND) {
                    res += grid.size() - i;
                }
            }
        }
        partBResult.first = res;
    }

    std::vector<std::vector<Day14::Tile>> Day14::MakeGrid(){
        std::vector<std::vector<Tile>> grid = {};
        for (auto& line : input) {
            grid.push_back({});
            for (auto& c : line) {
                switch (c) {
                case 'O':
                    grid.back().push_back(Tile::ROUND);
                    break;
                case '#':
                    grid.back().push_back(Tile::CUBE);
                    break;
                case '.':
                    grid.back().push_back(Tile::EMPTY);
                    break;
                }
            }
        }
        return grid;
    }

    void Day14::Tilt(std::vector<std::vector<Tile>>& grid, std::pair<int, int> dir) {
        if (dir.first == 1) {
            for (size_t y = 0; y < grid.size(); y++) {
                for (size_t x = grid[y].size() - 1; x != std::numeric_limits<size_t>::max(); x--) {
                    if (grid[y][x] != Tile::ROUND) { continue; }
                    grid[y][x] = Tile::EMPTY;
                    for (size_t dx = 1;; dx++) {
                        if (x + dx >= grid[y].size() || grid[y][x + dx] != Tile::EMPTY) {
                            grid[y][x + dx - 1] = Tile::ROUND;
                            break;
                        }
                    }
                }
            }
        }
        else if (dir.first == -1) {
            for (size_t y = 0; y < grid.size(); y++) {
                for (size_t x = 0; x < grid[y].size(); x++) {
                    if (grid[y][x] != Tile::ROUND) { continue; }
                    grid[y][x] = Tile::EMPTY;
                    for (size_t dx = 1;; dx++) {
                        if (x - dx == std::numeric_limits<size_t>::max() || grid[y][x - dx] != Tile::EMPTY) {
                            grid[y][x - dx + 1] = Tile::ROUND;
                            break;
                        }
                    }
                }
            }
        }
        else if (dir.second == 1) {
            for (size_t x = 0; x < grid[0].size(); x++) {
                for (size_t y = grid.size() - 1; y != std::numeric_limits<size_t>::max(); y--) {
                    if (grid[y][x] != Tile::ROUND) { continue; }
                    grid[y][x] = Tile::EMPTY;
                    for (size_t dy = 1;; dy++) {
                        if (y + dy >= grid.size() || grid[y + dy][x] != Tile::EMPTY) {
                            grid[y + dy - 1][x] = Tile::ROUND;
                            break;
                        }
                    }
                }
            }
        }
        else if (dir.second == -1) {
            for (size_t x = 0; x < grid[0].size(); x++) {
                for (size_t y = 0; y < grid.size(); y++) {
                    if (grid[y][x] != Tile::ROUND) { continue; }
                    grid[y][x] = Tile::EMPTY;
                    for (size_t dy = 1;; dy++) {
                        if (y - dy == std::numeric_limits<size_t>::max() || grid[y - dy][x] != Tile::EMPTY) {
                            grid[y - dy + 1][x] = Tile::ROUND;
                            break;
                        }
                    }
                }
            }
        }
    }

    void Day14::Cycle(std::vector<std::vector<Tile>>& grid) {
        Tilt(grid, { 0, -1 });
        Tilt(grid, { -1, 0 });
        Tilt(grid, { 0, 1 });
        Tilt(grid, { 1, 0 });
    }
}