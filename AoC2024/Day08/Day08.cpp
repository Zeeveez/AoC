#include "Day08.h"

#include <numeric>
#include <functional>

namespace AoC2024 {
    namespace Day08 {
        std::unordered_map<char, std::vector<std::pair<int, int>>> GetNodes(const std::vector<std::string>& input) {
            std::unordered_map<char, std::vector<std::pair<int, int>>> nodes = {};
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
            return nodes;
        }

        void AddAntinodesA(std::pair<int, int> a, std::pair<int, int> b, std::vector<std::string>& grid) {
            int dx = a.first - b.first;
            int dy = a.second - b.second;
            int newx1 = a.first + dx;
            int newx2 = b.first - dx;
            int newy1 = a.second + dy;
            int newy2 = b.second - dy;

            if (newy1 >= 0 && newy1 < grid.size() && newx1 >= 0 && newx1 < grid[newy1].size()) {
                grid[newy1][newx1] = '#';
            }
            if (newy2 >= 0 && newy2 < grid.size() && newx2 >= 0 && newx2 < grid[newy2].size()) {
                grid[newy2][newx2] = '#';
            }
        }

        void AddAntinodesB(std::pair<int, int> a, std::pair<int, int> b, std::vector<std::string>& grid) {
            int dx = a.first - b.first;
            int dy = a.second - b.second;
            int newx1 = a.first;
            int newx2 = b.first;
            int newy1 = a.second;
            int newy2 = b.second;

            while (newy1 >= 0 && newy1 < grid.size() && newx1 >= 0 && newx1 < grid[newy1].size()) {
                grid[newy1][newx1] = '#';
                newx1 += dx;
                newy1 += dy;
            }
            while (newy2 >= 0 && newy2 < grid.size() && newx2 >= 0 && newx2 < grid[newy2].size()) {
                grid[newy2][newx2] = '#';
                newx2 -= dx;
                newy2 -= dy;
            }
        }

        
        uint64_t CountAntinodes(const std::vector<std::string>& grid) {
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

        uint64_t Run(std::vector<std::string> input, std::function<void(std::pair<int, int> a, std::pair<int, int> b, std::vector<std::string>& grid)> antinodeFunc) {
            auto nodes = GetNodes(input);
            for (auto& kvp : nodes) {
                for (int i = 0; i < kvp.second.size(); i++) {
                    for (int j = 0; j < kvp.second.size(); j++) {
                        if (i == j) { continue; }
                        antinodeFunc(kvp.second[i], kvp.second[j], input);
                    }
                }
            }
            return CountAntinodes(input);
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(input, AddAntinodesA);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(input, AddAntinodesB);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - startTime };
        }
    }
}