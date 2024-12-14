#include "Day14.h"

#include <regex>
#include <iostream>

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

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto robots = PreProcessInput(input);
            int w = 101;
            int h = 103;
            for (auto& robot : robots) {
                robot.first.first = (robot.first.first + (robot.second.first + w) * 100) % w;
                robot.first.second = (robot.first.second + (robot.second.second + h) * 100) % h;
            }
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

            uint64_t res = 0;
            while (true) {
                res++;

                int64_t avgX = 0;
                int64_t avgY = 0;
                for (auto& robot : robots) {
                    robot.first.first = (robot.first.first + robot.second.first + w) % w;
                    robot.first.second = (robot.first.second + robot.second.second + h) % h;
                    avgX += robot.first.first;
                    avgY += robot.first.second;
                }
                avgX /= robots.size();
                avgY /= robots.size();

                int64_t avgDistance = 0; // manhattan
                for (auto& robot : robots) {
                    avgDistance += std::abs(robot.first.first + robot.first.second - avgX - avgY);
                }
                avgDistance /= robots.size();

                if (avgDistance < 20) {
                    break;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}