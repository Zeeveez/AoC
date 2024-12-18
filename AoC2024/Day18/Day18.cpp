#include "Day18.h"

#include <sstream>
#include <set>
#include <queue>

namespace AoC2024 {
    namespace Day18 {
        std::vector<std::pair<int, int>> dirs = {
            { 0, 1 },
            { 0, -1 },
            { -1, 0 },
            { 1, 0 },
        };

        std::vector<std::pair<int, int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<int, int>> coords = {};

            for (auto& line : input) {
                std::stringstream ss(line);
                std::string x;
                std::string y;
                std::getline(ss, x, ',');
                std::getline(ss, y, ',');
                coords.push_back(
                    {
                        std::stoi(x),
                        std::stoi(y)
                    }
                );
            }
            return coords;
        }

        int Simulate(const std::vector<int>& memory, int size, int timePassed) {
            std::set<std::tuple<int, int>> seen = {};
            std::queue<std::tuple<int, int, int>> queue = {};
            queue.push({ 0,0,0 });
            int res = 0;

            while (!queue.empty()) {
                auto [x, y, time] = queue.front(); queue.pop();
                if (seen.contains({ x, y })) { continue; }
                seen.insert({ x, y });

                if (x == size - 1 && y == size - 1) {
                    return time;
                }

                for (auto& dir : dirs) {
                    if (x + dir.first < 0 || x + dir.first >= size || y + dir.second < 0 || y + dir.second >= size) { continue; }
                    if (memory[(y + dir.second) * size + x + dir.first] >= timePassed) {
                        queue.push({ x + dir.first, y + dir.second, time + 1 });
                    }
                }
            }
            return -1;
        }

        std::vector<int> GetMemory(const std::vector<std::string>& input, int size) {
            auto coords = PreProcessInput(input);
            std::vector<int> memory(size * size, std::numeric_limits<int>::max());
            for (size_t i = 0; i < coords.size(); i++) {
                memory[coords[i].second * size + coords[i].first] = i;
            }
            return memory;
        }


        std::pair<int, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int size = 71;
            int timePassed = 1024;

            auto memory = GetMemory(input, size);
            auto res = Simulate(memory, size, timePassed);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int size = 71;
            int timePassed = 1024;

            auto memory = GetMemory(input, size);

            int lb = timePassed;
            int ub = input.size() - 1;

            while (lb != ub) {
                if (Simulate(memory, size, (ub + lb) / 2) == -1) {
                    ub = (ub + lb) / 2 - 1;
                }
                else {
                    lb = (ub + lb) / 2 + 1;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { input[lb - 1], endtime - starttime };
        }
    }
}