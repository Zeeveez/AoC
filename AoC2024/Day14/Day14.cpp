#include "Day14.h"

#include <regex>
#include <iostream>
#include <unordered_set>

namespace AoC2024 {
    namespace Day14 {
        std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>> robots = {};
            static const std::regex re("p=(\\d+),(\\d+) v=(\\-?\\d+),(\\-?\\d+)", std::regex::optimize);
            for (auto& line : input) {

                std::smatch sm;

                if (std::regex_search(line, sm, re)) {
                    robots.push_back(
                        {
                            {
                            std::stoi(sm[1]),
                            std::stoi(sm[2]),
                            },{
                            std::stoi(sm[3]),
                            std::stoi(sm[4])
                            }
                        }
                    );
                }
            }
            return robots;
        }

        void Run(std::vector<std::pair<std::pair<int64_t, int64_t>, std::pair<int64_t, int64_t>>>& robots, int64_t w, int64_t h, int64_t iter) {
            for (auto& robot : robots) {
                int64_t dx = robot.second.first < 0 ? w + robot.second.first : robot.second.first;
                int64_t dy = robot.second.second < 0 ? h + robot.second.second : robot.second.second;
                dx *= iter;
                dy *= iter;
                robot.first.first = (robot.first.first + dx) % w;
                robot.first.second = (robot.first.second + dy) % h;
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto robots = PreProcessInput(input);
            int w = 101;
            int h = 103;
            Run(robots, w, h, 100);
            int tl = 0;
            int tr = 0;
            int bl = 0;
            int br = 0;
            for (auto& robot : robots) {
                if (robot.first.first < w / 2 && robot.first.second < h / 2) {
                    tl++;
                }
                else if (robot.first.first > w / 2 && robot.first.second < h / 2) {
                    tr++;
                }
                if (robot.first.first < w / 2 && robot.first.second > h / 2) {
                    bl++;
                }
                else if (robot.first.first > w / 2 && robot.first.second > h / 2) {
                    br++;
                }
            }

            uint64_t res = tl * tr * bl * br;

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto robots = PreProcessInput(input);
            int w = 101;
            int h = 103;

            std::vector<std::vector<bool>> grid = {};
            for (int y = 0; y < h; y++) {
                grid.push_back({});
                for (int x = 0; x < w; x++) {
                    grid.back().push_back(false);
                }
            }

            uint64_t res = 0;
            while (true) {
                Run(robots, w, h, 1);
                res++;
                for (int y = 0; y < h; y++) {
                    for (int x = 0; x < w; x++) {
                        grid[y][x] = false;
                    }
                }
                for (auto& robot : robots) {
                    grid[robot.first.second][robot.first.first] = true;
                }

                std::unordered_set<int> seen = {};
                for (int y = 3; y < h - 3; y++) {
                    for (int x = 3; x < w - 3; x++) {
                        if (grid[y][x]
                            && grid[y - 1][x] && grid[y - 2][x] && grid[y - 3][x]
                            && grid[y + 1][x] && grid[y + 2][x] && grid[y + 3][x]
                            && grid[y][x - 1] && grid[y][x - 2] && grid[y][x - 3]
                            && grid[y][x + 1] && grid[y][x + 2] && grid[y][x + 3]) {
                            goto found;
                        }
                    }
                }
            }
        found:;

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}