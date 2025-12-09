#include <regex>
#include <numeric>

#include "Day14.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day14::Parse() {
        static const std::regex re("p=(\\d+),(\\d+) v=(\\-?\\d+),(\\-?\\d+)", std::regex::optimize);
        for (auto& line : rawData) {

            std::smatch sm;

            if (std::regex_search(line, sm, re)) {
                robots.push_back(
                    {
                        {
                            std::stoi(sm[1]),
                            std::stoi(sm[2]),
                        },
                        {
                            std::stoi(sm[3]),
                            std::stoi(sm[4])
                        }
                    }
                );
            }
        }
    }

    AoC::DayResult::PuzzleResult Day14::A() {
        auto robots = this->robots;

        int w = 101;
        int h = 103;
        int seconds = 100;
        for (auto& robot : robots) {
            robot.first.first = (robot.first.first + (robot.second.first + w) * seconds) % w;
            robot.first.second = (robot.first.second + (robot.second.second + h) * seconds) % h;
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
        return res;
    }

    AoC::DayResult::PuzzleResult Day14::B() {
        auto robots = this->robots;

        int w = 101;
        int h = 103;

        uint64_t res = 0;
        while (++res) {
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

            int64_t avgDistance = std::accumulate(
                robots.begin(), robots.end(), (int64_t)0,
                [avgX, avgY](int64_t acc, const auto& robot) {
                    // Manhattan distance
                    return acc + std::abs(robot.first.first + robot.first.second - avgX - avgY);
                }
            ) / robots.size();

            if (avgDistance < 20) {
                break;
            }
        }

        return res;
    }
}