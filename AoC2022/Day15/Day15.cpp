#include "Day15.h"

#include <regex>

namespace AoC2022 {
    namespace Day15 {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sensors = {};

            for (auto& line : input) {
                static const std::regex re("Sensor at x=(\\-?\\d+), y=(\\-?\\d+): closest beacon is at x=(\\-?\\d+), y=(\\-?\\d+)", std::regex::optimize);
                std::smatch sm;

                if (std::regex_search(line, sm, re)) {
                    sensors.push_back(
                        {
                            {
                                std::stoi(sm[1]),
                                std::stoi(sm[2])
                            },
                            {
                                std::stoi(sm[3]),
                                std::stoi(sm[4])
                            }
                        }
                    );
                }
            }

            return sensors;
        }

        int ManhattanDistance(const std::pair<int, int> a, const std::pair<int, int> b) {
            return std::abs(a.first - b.first) + std::abs(a.second - b.second);
        }

        std::vector<std::pair<int, int>> GetPossiblePositions(const std::pair<int, int> sensor, const std::pair<int, int> beacon) {
            std::vector<std::pair<int, int>> positions = {};
            int distance = ManhattanDistance(sensor, beacon) + 1;
            for (int x = -distance, y = 0; x <= 0; x++, y++) {
                positions.push_back(
                    {
                        sensor.first + x,
                        sensor.second + y
                    });
                positions.push_back(
                    {
                        sensor.first + x,
                        sensor.second - y
                    });
            }
            for (int x = 0, y = distance; x <= distance; x++, y--) {
                positions.push_back(
                    {
                        sensor.first + x,
                        sensor.second + y
                    });
                positions.push_back(
                    {
                        sensor.first + x,
                        sensor.second - y
                    });
            }
            return positions;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto sensors = PreProcessInput(input);
            int res = 0;
            for (int x = -10000000; x < 10000000; x++) {
                std::pair<int, int> pos = { x, 2000000 };
                bool canPlace = true;
                for (auto& sensor : sensors) {
                    if (ManhattanDistance(sensor.first, pos) <= ManhattanDistance(sensor.first, sensor.second)) {
                        canPlace = false;
                        break;
                    }
                }
                for (auto& sensor : sensors) {
                    if (sensor.second.first == x && sensor.second.second == 2000000) {
                        canPlace = true;
                        break;
                    }
                }

                if (!canPlace) {
                    res++;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto sensorBeaconPairs = PreProcessInput(input);
            uint64_t res = 0;

            for (auto& sensor : sensorBeaconPairs) {
                auto positions = GetPossiblePositions(sensor.first, sensor.second);
                for (auto& pos : positions) {
                    bool canPlace = true;
                    if (pos.first < 0 || pos.first > 4000000 || pos.second < 0 || pos.second > 4000000) { continue; }
                    for (auto& sensor : sensorBeaconPairs) {
                        if (ManhattanDistance(sensor.first, pos) <= ManhattanDistance(sensor.first, sensor.second)) {
                            canPlace = false;
                            break;
                        }
                    }
                    if (canPlace) {
                        res = pos.first * (uint64_t)4000000 + pos.second;
                        goto done;
                    }
                }
            }
            done:;

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}