#include "Day12.h"

#include <queue>

namespace AoC2022 {
    namespace Day12 {
        std::vector<std::vector<char>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<char>> grid = {};
            for (int y = 0; y < input.size(); y++) {
                grid.push_back({});
                for (int x = 0; x < input[y].size(); x++) {
                    grid[y].push_back(input[y][x]);
                }
            }
            return grid;
        }

        int HashPair(std::pair<int, int> p) {
            return p.second * 2000 + p.first;
        }

        std::pair<int, int> GetStartAndEnd(std::vector<std::vector<char>> grid) {
            int start = 0;
            int end = 0;
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    if (grid[y][x] == 'S') {
                        start = HashPair({ x, y });
                    }
                    else if (grid[y][x] == 'E') {
                        end = HashPair({ x, y });
                    }
                }
            }
            return { start, end };
        }

        std::set<int> GetExtraStarts(std::vector<std::vector<char>> grid) {
            std::set<int> starts = {};
            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    if (grid[y][x] == 'a') {
                        starts.insert(HashPair({ x, y }));
                    }
                }
            }
            return starts;
        }

        std::unordered_map<int, std::vector<int>> GenerateGraph(const std::vector<std::vector<char>>& grid) {
            std::unordered_map<int, std::vector<int>> graph = {};

            std::vector<std::pair<int, int>> moves = {
                {  1,  0 },
                { -1,  0 },
                {  0,  1 },
                {  0, -1 }
            };

            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    for (auto& move : moves) {
                        int dx = move.first;
                        int dy = move.second;
                        if (y + dy < 0 || y + dy >= grid.size() || x + dx < 0 || x + dx >= grid[y + dy].size()) {
                            continue;
                        }
                        auto from = (grid[y][x] == 'S'
                                     ? 'a'
                                     : (grid[y][x] == 'E'
                                        ? 'z'
                                        : grid[y][x]
                                        )
                                     );
                        auto to = (grid[y + dy][x + dx] == 'S'
                                   ? 'a'
                                   : (grid[y + dy][x + dx] == 'E'
                                      ? 'z'
                                      : grid[y + dy][x + dx]
                                      )
                                   );
                        if (to <= from + 1) {
                            if (!graph.contains(HashPair({ x, y }))) {
                                graph.insert({ HashPair({ x, y }), {} });
                            }
                            graph[HashPair({ x, y })].push_back(HashPair({ x + dx, y + dy }));
                        }
                    }
                }
            }
            return graph;
        }

        std::unordered_map<int, std::vector<int>> GenerateReverseGraph(const std::vector<std::vector<char>>& grid) {
            std::unordered_map<int, std::vector<int>> graph = {};

            std::vector<std::pair<int, int>> moves = {
                {  1,  0 },
                { -1,  0 },
                {  0,  1 },
                {  0, -1 }
            };

            for (int y = 0; y < grid.size(); y++) {
                for (int x = 0; x < grid[y].size(); x++) {
                    for (auto& move : moves) {
                        int dx = move.first;
                        int dy = move.second;
                        if (y + dy < 0 || y + dy >= grid.size() || x + dx < 0 || x + dx >= grid[y + dy].size()) {
                            continue;
                        }
                        auto to = (grid[y][x] == 'S'
                                   ? 'a'
                                   : (grid[y][x] == 'E'
                                      ? 'z'
                                      : grid[y][x]
                                      )
                                   );
                        auto from = (grid[y + dy][x + dx] == 'S'
                                     ? 'a'
                                     : (grid[y + dy][x + dx] == 'E'
                                        ? 'z'
                                        : grid[y + dy][x + dx]
                                        )
                                     );
                        if (to <= from + 1) {
                            if (!graph.contains(HashPair({ x, y }))) {
                                graph.insert({ HashPair({ x, y }), {} });
                            }
                            graph[HashPair({ x, y })].push_back(HashPair({ x + dx, y + dy }));
                        }
                    }
                }
            }
            return graph;
        }

        int TraverseGraph(const std::unordered_map<int, std::vector<int>>& graph, int start, std::set<int> ends) {
            std::queue<std::pair<int, int>> moves = { };
            std::set<int> seen = {};
            moves.push({ start, 0 });
            while (moves.size()) {
                auto [pos, steps] = moves.front(); moves.pop();
                if (ends.contains(pos)) {
                    return steps;
                }
                if (seen.contains(pos)) { continue; }
                seen.insert(pos);

                for (auto& next : graph.at(pos)) {
                    moves.push({ next, steps + 1 });
                }
            }
            return 999999;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto grid = PreProcessInput(input);
            auto [start, end] = GetStartAndEnd(grid);
            auto graph = GenerateGraph(grid);

            int res = TraverseGraph(graph, start, { end });

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto grid = PreProcessInput(input);
            auto [start, end] = GetStartAndEnd(grid);
            auto starts = GetExtraStarts(grid);
            starts.insert(start);
            auto graph = GenerateReverseGraph(grid);

            int res = TraverseGraph(graph, end, starts);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}