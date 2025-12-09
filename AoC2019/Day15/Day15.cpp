#include <map>
#include <numeric>

#include "Day15.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day15::A() {
        IntCodeCPU computer(rawData);
        std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> arena = { {{0,0},1} };
        std::int64_t x = 0;
        std::int64_t y = 0;
        while (SearchMaze(computer, x, y, arena)) {}

        auto start = FindEnd(arena);
        auto end = FindStart(arena);
        auto maze = MapToMaze(arena);
        FloodFill(maze, end);
        return maze[start.first][start.second];
    }

    AoC::DayResult::PuzzleResult Day15::B() {
        IntCodeCPU computer(rawData);
        std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> arena = { {{0,0},1} };
        std::int64_t x = 0;
        std::int64_t y = 0;
        while (SearchMaze(computer, x, y, arena)) {}

        auto end = FindEnd(arena);
        auto maze = MapToMaze(arena);
        FloodFill(maze, end);
        int max = 0;
        for (int x = 0; x < maze.size(); x++) {
            for (int y = 0; y < maze[0].size(); y++) {
                max = maze[x][y] > max ? maze[x][y] : max;
            }
        }
        return max;
    }

    std::pair<std::int64_t, std::int64_t> Day15::FindUnsearched(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& mazeMap) {
        for (auto& pos : mazeMap) {
            if (pos.second != 0) {
                for (int dx = -1; dx < 2; dx++) {
                    for (int dy = -1; dy < 2; dy++) {
                        if (std::abs(dx) + std::abs(dy) == 1) {
                            if (mazeMap.count({ pos.first.first + dx, pos.first.second + dy }) == 0) {
                                return { pos.first.first + dx, pos.first.second + dy };
                            }
                        }
                    }
                }
            }
        }
        return { -999999,-999999 };
    }

    void Day15::TraversePath(IntCodeCPU& computer, std::int64_t& x, std::int64_t& y, std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& arena, std::vector<std::pair<std::int64_t, std::int64_t>> path) {
        for (int i = path.size() - 1; i > -1; i--) {
            int dir = 0;
            if (path[i].first - x == -1) {
                computer.Input(3);
            }
            else if (path[i].first - x == 1) {
                computer.Input(4);
            }
            else if (path[i].second - y == -1) {
                computer.Input(1);
            }
            else {
                computer.Input(2);
            }
            computer.RunToOutput();
            arena[{path[i].first, path[i].second}] = computer.Output();
            if (computer.Output() != 0) {
                x = path[i].first;
                y = path[i].second;
            }
            else {
                return;
            }
        }
    }

    std::vector<std::pair<std::int64_t, std::int64_t>> Day15::GetPath(std::int64_t x, std::int64_t y, std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& arena, std::pair<std::int64_t, std::int64_t> destination) {
        std::map<std::pair<std::int64_t, std::int64_t>, std::pair<std::int64_t, std::int64_t>> pathMap = {};
        std::vector<std::pair<std::int64_t, std::int64_t>> toCheck = { {x,y} };
        std::vector<std::pair<std::int64_t, std::int64_t>> checked = { };
        while (pathMap.count(destination) == 0 && toCheck.size() > 0) {
            std::pair<std::int64_t, std::int64_t> checkPos = toCheck[toCheck.size() - 1];
            toCheck.pop_back();
            if (std::find(checked.begin(), checked.end(), checkPos) == checked.end()) {
                checked.push_back(checkPos);
                for (int dx = -1; dx < 2; dx++) {
                    for (int dy = -1; dy < 2; dy++) {
                        if (std::abs(dx) + std::abs(dy) == 1) {
                            if (pathMap.count({ checkPos.first + dx, checkPos.second + dy }) == 0) {
                                if (checkPos.first + dx == x && checkPos.second + dy == y) {
                                    continue;
                                }
                                else if (checkPos.first + dx == destination.first && checkPos.second + dy == destination.second) {
                                    pathMap[{checkPos.first + dx, checkPos.second + dy }] = { checkPos.first, checkPos.second };
                                }
                                else if (arena.count({ checkPos.first + dx, checkPos.second + dy }) == 1 && arena[{checkPos.first + dx, checkPos.second + dy }] != 0) {
                                    toCheck.push_back({ checkPos.first + dx, checkPos.second + dy });
                                    pathMap[{checkPos.first + dx, checkPos.second + dy }] = { checkPos.first, checkPos.second };
                                }
                            }
                        }
                    }
                }
            }
        }

        std::vector<std::pair<std::int64_t, std::int64_t>> path = {};
        while (pathMap.count(destination) == 1) {
            path.push_back(destination);
            destination = pathMap[destination];
        }
        return path;
    }

    bool Day15::SearchMaze(IntCodeCPU& computer, std::int64_t& x, std::int64_t& y, std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t>& arena) {
        std::pair<std::int64_t, std::int64_t> unsearched = FindUnsearched(arena);
        if (unsearched.first == -999999) { return false; }
        TraversePath(computer, x, y, arena, GetPath(x, y, arena, unsearched));
        return true;
    }

    std::pair<std::int64_t, std::int64_t> Day15::FindStart(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> mazeMap) {
        int xMin = (*std::min_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int xMax = (*std::max_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int yMin = (*std::min_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;
        int yMax = (*std::max_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;
        return { 0 - xMin,0 - yMin };
    }

    std::pair<std::int64_t, std::int64_t> Day15::FindEnd(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> mazeMap) {
        int xMin = (*std::min_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int xMax = (*std::max_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int yMin = (*std::min_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;
        int yMax = (*std::max_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;

        for (int x = xMin; x < xMax + 1; x++) {
            for (int y = yMin; y < yMax + 1; y++) {
                if (mazeMap[{x, y}] == 2) {
                    return { x - xMin,y - yMin };
                }
            }
        }
        return { -1,-1 };
    }

    std::vector<std::vector<std::int64_t>> Day15::MapToMaze(std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> mazeMap) {
        int xMin = (*std::min_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int xMax = (*std::max_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int yMin = (*std::min_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;
        int yMax = (*std::max_element(mazeMap.begin(), mazeMap.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;

        std::vector<std::vector<std::int64_t>> output = {};
        for (int x = xMin; x < xMax + 1; x++) {
            output.push_back({});
            for (int y = yMin; y < yMax + 1; y++) {
                output[x - xMin].push_back(mazeMap[{x, y}] == 0 ? -1 : 0);
            }
        }
        return output;
    }

    void Day15::FloodFill(std::vector<std::vector<std::int64_t>>& maze, std::pair<std::int64_t, std::int64_t> origin, int n) {
        if (origin.first > -1 && origin.first < maze.size() && origin.second > -1 && origin.second < maze[0].size()) {
            if (maze[origin.first][origin.second] == 0) {
                maze[origin.first][origin.second] = n;
                for (int dx = -1; dx < 2; dx++) {
                    for (int dy = -1; dy < 2; dy++) {
                        if (std::abs(dx) + std::abs(dy) == 1) {
                            FloodFill(maze, { origin.first + dx,origin.second + dy }, n + 1);
                        }
                    }
                }
            }
        }
    }
}