#include "Day17.h"

#include <map>

namespace AoC2022 {
    namespace Day17 {
        static std::vector<Rock> rocks = {
            // ####
            Rock(
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x - 1];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x + 4];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y - 1][x] || grid[y - 1][x + 1] || grid[y - 1][x + 2] || grid[y - 1][x + 3];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    grid[y][x] = true;
                    grid[y][x + 1] = true;
                    grid[y][x + 2] = true;
                    grid[y][x + 3] = true;
                    return true;
                },
                1
            ),

            // .#.
            // ###
            // .#.
            Rock(
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x] || grid[y - 1][x - 1] || grid[y - 2][x];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x + 2] || grid[y - 1][x + 3] || grid[y - 2][x + 2];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y - 2][x] || grid[y - 3][x + 1] || grid[y - 2][x + 2];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    grid[y][x + 1] = true;
                    grid[y - 1][x] = true;
                    grid[y - 1][x + 1] = true;
                    grid[y - 1][x + 2] = true;
                    grid[y - 2][x + 1] = true;
                    return true;
                },
                3
            ),

            // ..#
            // ..#
            // ###
            Rock(
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x + 1] || grid[y - 1][x + 1] || grid[y - 2][x - 1];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x + 3] || grid[y - 1][x + 3] || grid[y - 2][x + 3];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y - 3][x] || grid[y - 3][x + 1] || grid[y - 3][x + 2];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    grid[y][x + 2] = true;
                    grid[y - 1][x + 2] = true;
                    grid[y - 2][x] = true;
                    grid[y - 2][x + 1] = true;
                    grid[y - 2][x + 2] = true;
                    return true;
                },
                3
            ),

            // #
            // #
            // #
            // #
            Rock(
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x - 1] || grid[y - 1][x - 1] || grid[y - 2][x - 1] || grid[y - 3][x - 1];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x + 1] || grid[y - 1][x + 1] || grid[y - 2][x + 1] || grid[y - 3][x + 1];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y - 4][x];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    grid[y][x] = true;
                    grid[y - 1][x] = true;
                    grid[y - 2][x] = true;
                    grid[y - 3][x] = true;
                    return true;
                },
                4
            ),

            // ##
            // ##
            Rock(
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x - 1] || grid[y - 1][x - 1];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y][x + 2] || grid[y - 1][x + 2];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    return grid[y - 2][x] || grid[y - 2][x + 1];
                },
                [](int x, int y, std::vector<std::vector<bool>>& grid) {
                    grid[y][x] = true;
                    grid[y][x + 1] = true;
                    grid[y - 1][x] = true;
                    grid[y - 1][x + 1] = true;
                    return true;
                },
                2
            )
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<char>& input, int rockCount) {
            auto starttime = std::chrono::high_resolution_clock::now();

            std::vector<std::vector<bool>> chamber = {};
            chamber.push_back({ true, true, true, true, true, true, true, true, true });
            for (int i = 0; i < rockCount * 10; i++) {
                chamber.push_back({ true, false, false, false, false, false, false, false, true });
            }

            int startY = 0;
            int push = 0;
            for (int i = 0; i < rockCount; i++) {
                Rock& rock = rocks[i % 5];
                int x = 3;
                startY += 3 + rock.height;
                int y = startY;
                while (true) {
                    switch (input[push++ % input.size()]) {
                    case '>':
                        if (!rock.rightCollision(x, y, chamber)) {
                            x++;
                        }
                        break;
                    case '<':
                        if (!rock.leftCollision(x, y, chamber)) {
                            x--;
                        }
                        break;
                    }
                    if (rock.downCollision(x, y, chamber)) {
                        rock.place(x, y, chamber);
                        break;
                    }
                    else {
                        y--;
                    }
                }
                while (true) {
                    for (int x = 1; x < 8; x++) {
                        if (chamber[startY][x]) {
                            goto done;
                        }
                    }
                    startY--;
                }
            done:;
            }

            int res = startY;

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<char>& input) {
            const uint64_t ROCKCOUNT = 1000000000000;
            auto starttime = std::chrono::high_resolution_clock::now();
            std::map<std::pair<uint64_t, uint64_t>, std::tuple<int, uint64_t, uint64_t>> seen = {};
            uint64_t state1 = 0;
            uint64_t state2 = 0;

            std::vector<std::vector<bool>> chamber = {};
            chamber.push_back({ true, true, true, true, true, true, true, true, true });
            for (int i = 0; i < input.size() * 10; i++) {
                chamber.push_back({ true, false, false, false, false, false, false, false, true });
            }

            uint64_t res = 0;

            int startY = 0;
            int push = 0;
            bool handledRepeats = false;
            for (uint64_t i = 0; i < ROCKCOUNT; i++) {
                Rock& rock = rocks[i % 5];
                int x = 3;
                startY += 3 + rock.height;
                int y = startY;
                while (true) {
                    switch (input[push++]) {
                    case '>':
                        if (!rock.rightCollision(x, y, chamber)) {
                            x++;
                        }
                        break;
                    case '<':
                        if (!rock.leftCollision(x, y, chamber)) {
                            x--;
                        }
                        break;
                    }
                    push %= input.size();
                    if (rock.downCollision(x, y, chamber)) {
                        rock.place(x, y, chamber);
                        break;
                    }
                    else {
                        y--;
                    }
                }
                while (true) {
                    for (int x = 1; x < 8; x++) {
                        if (chamber[startY][x]) {
                            goto done;
                        }
                    }
                    startY--;
                }
            done:;

                if (!handledRepeats) {
                    state2 = (state2 << 8 | state1 >> 56);
                    state1 = (state1 << 8) | (chamber[y][1] << 7) | (chamber[y][2] << 6) | (chamber[y][3] << 5) | (chamber[y][4] << 4) | (chamber[y][5] << 3) | (chamber[y][6] << 2) | (chamber[y][7] << 1);
                    if (seen.contains({ state1, state2 })) {
                        if (std::get<0>(seen[{ state1, state2 }]) == push && std::get<1>(seen[{ state1, state2 }]) % 5 == i % 5) {
                            uint64_t repeatStart = std::get<1>(seen[{ state1, state2 }]);
                            uint64_t period = i - repeatStart;

                            uint64_t noPeriodsLeft = (ROCKCOUNT - i) / period;

                            uint64_t rocksInRepeats = period * noPeriodsLeft;

                            uint64_t heightChangePerPeriod = startY - std::get<2>(seen[{ state1, state2 }]);
                            uint64_t heightChangeFromRepeats = noPeriodsLeft * heightChangePerPeriod;

                            i += rocksInRepeats;
                            res += heightChangeFromRepeats;
                            handledRepeats = true;
                        }
                    }
                    seen[{ state1, state2 }] = { push, i, startY };
                }
            }

            res += startY;

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}