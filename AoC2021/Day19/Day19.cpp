#include "Day19.h"

#include <sstream>
#include <algorithm>

namespace AoC2021 {
    namespace Day19 {
        std::vector<std::vector<std::vector<int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<std::vector<int>>> scannerBeacons = {};
            for (int i = 0; i < input.size(); i++) {
                if (input[i][1] == '-') {
                    scannerBeacons.push_back({});
                    i += 3;
                }
                else {
                    std::vector<int> beacon = {};
                    std::stringstream allNums(input[i]);
                    std::string currentNum;
                    while (std::getline(allNums, currentNum, ',')) {
                        beacon.push_back(std::stoi(currentNum));
                    }
                    scannerBeacons[scannerBeacons.size() - 1].push_back(beacon);
                }
            }
            return scannerBeacons;
        }

        std::vector<int> Transform(const std::vector<int>& input, int transformation) {
            std::vector<int> output = {};
            for (int i = 0; i < input.size(); i++) {
                output.push_back(transformations[transformation][i].first * input[transformations[transformation][i].second]);
            }
            return output;
        }

        std::vector<std::vector<int>> Transform(const std::vector<std::vector<int>>& input, int transformation) {
            std::vector<std::vector<int>> output = {};
            for (auto& beacon : input) {
                output.push_back(Transform(beacon, transformation));
            }
            return output;
        }

        bool AddToMap(std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& scanners, const std::vector<std::vector<int>>& beacons, int transformation) {
            auto transBeacons = Transform(beacons, transformation);
            for (int mapIdx = 0; mapIdx < map.size(); mapIdx++) {
                for (int beaconIdx = 0; beaconIdx < transBeacons.size(); beaconIdx++) {
                    int xDiff = map[mapIdx][0] - transBeacons[beaconIdx][0];
                    int yDiff = map[mapIdx][1] - transBeacons[beaconIdx][1];
                    int zDiff = map[mapIdx][2] - transBeacons[beaconIdx][2];

                    int matches = 0;
                    for (int i = 0; i < map.size(); i++) {
                        for (int j = 0; j < transBeacons.size(); j++) {
                            int testXDiff = map[i][0] - transBeacons[j][0];
                            int testYDiff = map[i][1] - transBeacons[j][1];
                            int testZDiff = map[i][2] - transBeacons[j][2];
                            if (xDiff == testXDiff && yDiff == testYDiff && zDiff == testZDiff) {
                                matches++;
                            }
                        }
                    }
                    if (matches >= 12) {
                        for (int j = 0; j < transBeacons.size(); j++) {
                            int newX = transBeacons[j][0] + xDiff;
                            int newY = transBeacons[j][1] + yDiff;
                            int newZ = transBeacons[j][2] + zDiff;

                            bool alreadyPresent = false;
                            for (int i = 0; i < map.size(); i++) {
                                if (newX == map[i][0] && newY == map[i][1] && newZ == map[i][2]) {
                                    alreadyPresent = true;
                                    break;
                                }
                            }

                            if (!alreadyPresent) {
                                map.push_back({ newX, newY, newZ });
                            }
                        }

                        scanners.push_back({ xDiff, yDiff, zDiff });
                        return true;
                    }
                }
            }

            return false;
        }

        bool AddToMap(std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& scanners, const std::vector<std::vector<int>>& beacons) {
            for (int i = 0; i < transformations.size(); i++) {
                if (AddToMap(map, scanners, beacons, i)) {
                    return true;
                }
            }
            return false;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto beacons = PreProcessInput(input);

            auto beaconMap = beacons[0];
            std::vector<std::vector<int>> scanners = { { 0, 0, 0 } };

            std::vector<bool> addedToMap = { true };
            for (int i = 1; i < beacons.size(); i++) { addedToMap.push_back(false); }

            bool mapUpdated = true;
            while (mapUpdated) {
                mapUpdated = false;
                for (int i = 0; i < beacons.size(); i++) {
                    if (!addedToMap[i]) {
                        addedToMap[i] = AddToMap(beaconMap, scanners, beacons[i]);
                        if (addedToMap[i]) { mapUpdated = true; }
                    }
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { beaconMap.size(), endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto beacons = PreProcessInput(input);

            auto beaconMap = beacons[0];
            std::vector<std::vector<int>> scanners = { { 0, 0, 0 } };

            std::vector<bool> addedToMap = { true };
            for (int i = 1; i < beacons.size(); i++) { addedToMap.push_back(false); }

            bool mapUpdated = true;
            while (mapUpdated) {
                mapUpdated = false;
                for (int i = 0; i < beacons.size(); i++) {
                    if (!addedToMap[i]) {
                        addedToMap[i] = AddToMap(beaconMap, scanners, beacons[i]);
                        if (addedToMap[i]) { mapUpdated = true; }
                    }
                }
            }

            int maxDist = 0;
            for (auto& scanner1 : scanners) {
                for (auto& scanner2 : scanners) {
                    int dist = std::abs(scanner1[0] - scanner2[0])
                        + std::abs(scanner1[1] - scanner2[1])
                        + std::abs(scanner1[2] - scanner2[2]);
                    maxDist = std::max(maxDist, dist);
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { maxDist, endTime - startTime };
        }
    }
}