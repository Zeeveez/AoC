#include "Day17.h"

#include <algorithm>
#include <cmath>

namespace AoC2021 {
    namespace Day17 {
        std::pair<std::pair<int, int>, std::pair<int, int>> PreProcessInput(const std::vector<std::string>& input) {
            std::string inputCoordString = input[input.size() - 2] + input[input.size() - 1];
            std::vector<std::string> nums = { "", "", "", "" };
            int currNum = 0;
            for (int i = 1; i < inputCoordString.size(); i++) {
                char prev = inputCoordString[i - 1];
                char curr = inputCoordString[i];
                if ((prev == '=' || prev == '.' || prev == '-' || (prev >= '0' && prev <= '9'))
                    && (curr == '-' || (curr >= '0' && curr <= '9'))) {
                    nums[currNum] += curr;
                }
                else {
                    if (nums[currNum].size() != 0) { currNum++; }
                }
            }

            return {
                { std::stoi(nums[0]), std::stoi(nums[1]) },
                { std::stoi(nums[2]), std::stoi(nums[3]) }
            };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [xBounds, yBounds] = PreProcessInput(input);

            int maxY = 0;
            for (int initXVel = 0; initXVel <= xBounds.second; initXVel++) {
                for (int initYVel = yBounds.first; initYVel < 100; initYVel++) {
                    int x = 0;
                    int y = 0;
                    int xVel = initXVel;
                    int yVel = initYVel;
                    int maxYThisRun = 0;
                    bool validRun = false;
                    while(x < xBounds.second && y > yBounds.first){
                        x += xVel;
                        y += yVel;
                        if (xVel > 0) { xVel--; }
                        else if (xVel < 0) { xVel++; }
                        yVel -= 1;
                        if (x >= xBounds.first && x <= xBounds.second && y >= yBounds.first && y <= yBounds.second) {
                            validRun = true;
                        }
                        maxYThisRun = std::max(maxYThisRun, y);
                    }

                    if (validRun) {
                        maxY = std::max(maxYThisRun, maxY);
                    }
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { maxY, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [xBounds, yBounds] = PreProcessInput(input);

            int validLaunches = 0;
            for (int initXVel = 0; initXVel <= xBounds.second; initXVel++) {
                for (int initYVel = yBounds.first; initYVel < 100; initYVel++) {
                    int x = 0;
                    int y = 0;
                    int xVel = initXVel;
                    int yVel = initYVel;
                    while (x < xBounds.second && y > yBounds.first) {
                        x += xVel;
                        y += yVel;
                        if (xVel > 0) { xVel--; }
                        else if (xVel < 0) { xVel++; }
                        yVel -= 1;
                        if (x >= xBounds.first && x <= xBounds.second && y >= yBounds.first && y <= yBounds.second) {
                            validLaunches++; break;
                        }
                    }
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { validLaunches, endTime - startTime };
        }
    }
}