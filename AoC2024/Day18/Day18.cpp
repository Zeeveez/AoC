#include "Day18.h"

#include <regex>
#include <unordered_set>
#include <queue>
#include <set>
#include <iostream>

namespace AoC2024 {
    namespace Day18 {
        std::vector<std::pair<uint64_t, uint64_t>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<uint64_t, uint64_t>> coords = {};

            static const std::regex re("(\\d+),(\\d+)", std::regex::optimize);
            for (auto& line : input) {
                std::string::const_iterator searchStart(line.cbegin());
                std::smatch sm;
                while (std::regex_search(searchStart, line.cend(), sm, re)) {
                    coords.push_back(
                        {
                            std::stoi(sm[1]),
                            std::stoi(sm[2])
                        }
                    );
                    searchStart = sm.suffix().first;
                }
            }
            return coords;
        }

        int Simulate(const std::vector<std::string>& input, int size, int simulate) {
            std::unordered_set<uint64_t> memory = {};
            auto coords = PreProcessInput(input);
            size_t i = 0;
            for (int i = 0; i < simulate; i++) {
                memory.insert(coords[i].second * size + coords[i].first);
            }

            std::vector<std::pair<int, int>> dirs = {
                {0,1},
                {0,-1},
                {1,0},
                {-1,0}
            };

            std::set<std::tuple<int, int>> seen = {};
            std::queue<std::tuple<int, int, uint64_t>> queue = {};
            queue.push({ 0,0,0 });
            uint64_t res = 0;

            while (!queue.empty()) {
                auto [x, y, time] = queue.front(); queue.pop();
                if (seen.contains({ x, y })) { continue; }
                seen.insert({ x, y });

                if (x == size - 1 && y == size - 1) {
                    return time;
                }

                for (auto& dir : dirs) {
                    if (x + dir.first < 0 || x + dir.first >= size || y + dir.second < 0 || y + dir.second >= size) { continue; }
                    if (!memory.contains((y + dir.second) * size + x + dir.first)) {
                        queue.push({ x + dir.first, y + dir.second, time + 1 });
                    }
                }
            }
            return -1;
        }


        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto res = Simulate(input, 71, 1024);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
            auto coords = PreProcessInput(input);

            std::string res = "";
            int lb = 1024;
            int ub = coords.size() - 1;

            while (lb != ub) {
                if (Simulate(input, 71, (ub + lb) / 2) == -1) {
                    ub = (ub + lb) / 2 - 1;
                }
                else {
                    lb = (ub + lb) / 2 + 1;
                }
            }

            res = std::to_string(coords[lb - 1].first) + ',' + std::to_string(coords[lb - 1].second);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}