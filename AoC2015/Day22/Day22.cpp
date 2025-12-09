#include "Day22.h"

#include <regex>
#include <numeric>

#include <iostream>

namespace AoC2015 {
    namespace Day22 {
        std::vector<Instruction> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<Instruction> output = {};

            const std::regex re("(-?\\d+)[^\\d\\-]*(-?\\d+)[^\\d\\-]*(-?\\d+)[^\\d\\-]*(-?\\d+)[^\\d\\-]*(-?\\d+)[^\\d\\-]*(-?\\d+)");
            std::smatch sm;

            for (int i = 0; i < input.size(); i += 2) {
                bool state = input[i] == "on";
                if (std::regex_search(input[i + 1], sm, re)) {
                    Cube cube;
                    cube.p1.x = std::stoi(sm[1]);
                    cube.p1.y = std::stoi(sm[3]);
                    cube.p1.z = std::stoi(sm[5]);
                    cube.p2.x = std::stoi(sm[2]);
                    cube.p2.y = std::stoi(sm[4]);
                    cube.p2.z = std::stoi(sm[6]);
                    output.push_back({ state, cube });
                }
            }

            return output;
        }

        bool ContainedBy(const Cube& existingCube, const Cube& cube) {
            if (cube.p1.x <= existingCube.p1.x && cube.p2.x >= existingCube.p2.x) {
                if (cube.p1.y <= existingCube.p1.y && cube.p2.y >= existingCube.p2.y) {
                    if (cube.p1.z <= existingCube.p1.z && cube.p2.z >= existingCube.p2.z) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool OverlapedBy(const Cube& existingCube, const Cube& cube) {
            if (cube.p2.x >= existingCube.p1.x && cube.p1.x <= existingCube.p2.x) {
                if (cube.p2.y >= existingCube.p1.y && cube.p1.y <= existingCube.p2.y) {
                    if (cube.p2.z >= existingCube.p1.z && cube.p1.z <= existingCube.p2.z) {
                        return true;
                    }
                }
            }
            return false;
        }

        std::vector<Cube> Add(const std::vector<Cube>& currentCubes, const Cube& cube) {
            // Cutting the new cube out of existing cubes and then re-adding means we won't have overlapping cubes
            auto cubes = Cut(currentCubes, cube);
            cubes.push_back(cube);
            return cubes;
        }

        std::vector<Cube> Cut(const std::vector<Cube>& currentCubes, const Cube& cube) {
            std::vector<Cube> cubes = {};
            for (auto& currentCube : currentCubes) {
                if (!ContainedBy(currentCube, cube)) {
                    if (OverlapedBy(currentCube, cube)) {
                        for (auto& newCube : Cut(currentCube, cube)) {
                            cubes.push_back(newCube);
                        }
                    }
                    else {
                        cubes.push_back(currentCube);
                    }
                }
            }
            return cubes;
        }

        std::vector<Cube> Cut(const Cube& existingCube, const Cube& cube) {
            std::vector<Cube> newCubes;
            Cube remainingCube = existingCube;

            // Cut off excess negative x to keep
            if (remainingCube.p1.x < cube.p1.x) {
                Cube newCube = remainingCube;
                newCube.p2.x = cube.p1.x - 1;
                newCubes.push_back(newCube);
                remainingCube.p1.x = cube.p1.x;
            }

            // Cut off excess positive x to keep
            if (remainingCube.p2.x > cube.p2.x) {
                Cube newCube = remainingCube;
                newCube.p1.x = cube.p2.x + 1;
                newCubes.push_back(newCube);
                remainingCube.p2.x = cube.p2.x;
            }

            // Cut off excess negative y to keep
            if (remainingCube.p1.y < cube.p1.y) {
                Cube newCube = remainingCube;
                newCube.p2.y = cube.p1.y - 1;
                newCubes.push_back(newCube);
                remainingCube.p1.y = cube.p1.y;
            }

            // Cut off excess positive y to keep
            if (remainingCube.p2.y > cube.p2.y) {
                Cube newCube = remainingCube;
                newCube.p1.y = cube.p2.y + 1;
                newCubes.push_back(newCube);
                remainingCube.p2.y = cube.p2.y;
            }

            // Cut off excess negative z to keep
            if (remainingCube.p1.z < cube.p1.z) {
                Cube newCube = remainingCube;
                newCube.p2.z = cube.p1.z - 1;
                newCubes.push_back(newCube);
                remainingCube.p1.z = cube.p1.z;
            }

            // Cut off excess positive z to keep
            if (remainingCube.p2.z > cube.p2.z) {
                Cube newCube = remainingCube;
                newCube.p1.z = cube.p2.z + 1;
                newCubes.push_back(newCube);
                remainingCube.p2.z = cube.p2.z;
            }

            // Anything remaining of remainingCube is contained by cube and is being cut out

            return newCubes;
        }

        uint64_t Count(const std::vector<Cube>& currentCubes) {
            uint64_t c = 0;
            for (auto& cube : currentCubes) {
                uint64_t dx = std::abs(cube.p2.x - cube.p1.x) + 1;
                uint64_t dy = std::abs(cube.p2.y - cube.p1.y) + 1;
                uint64_t dz = std::abs(cube.p2.z - cube.p1.z) + 1;
                c += dx * dy * dz;
            }
            return c;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto instructions = PreProcessInput(input);

            std::vector<Cube> cubes = {};
            for (auto& instruction : instructions) {
                Cube cube = instruction.second;

                if (cube.p1.x < -50 || cube.p1.x > 50
                    || cube.p1.y < -50 || cube.p1.y > 50
                    || cube.p1.z < -50 || cube.p1.z > 50
                    || cube.p2.x < -50 || cube.p2.x > 50
                    || cube.p2.y < -50 || cube.p2.y > 50
                    || cube.p2.z < -50 || cube.p2.z > 50) {
                    break;
                }

                if (instruction.first) {
                    cubes = Add(cubes, cube);
                }
                else {
                    cubes = Cut(cubes, cube);
                }
            }
            auto count = Count(cubes);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { count, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto instructions = PreProcessInput(input);

            std::vector<Cube> cubes = {};
            for (auto& instruction : instructions) {
                Cube cube = instruction.second;
                if (instruction.first) {
                    cubes = Add(cubes, cube);
                }
                else {
                    cubes = Cut(cubes, cube);
                }
            }
            auto count = Count(cubes);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { count, endTime - startTime };
        }
    }
}