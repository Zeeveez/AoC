#ifndef DAY22_H
#define DAY22_H

#include <vector>
#include <string>
#include <chrono>
#include <tuple>

namespace AoC2021 {
    namespace Day22 {
        struct Point {
            int x;
            int y;
            int z;
        };
        struct Cube {
            Point p1;
            Point p2;
        };

        typedef std::pair<bool, Cube> Instruction;

        std::vector<Instruction> PreProcessInput(const std::vector<std::string>& input);

        bool ContainedBy(const Cube& existingCube, const Cube& cube);
        bool OverlapedBy(const Cube& existingCube, const Cube& cube);

        std::vector<Cube> Add(const std::vector<Cube>& currentCubes, const Cube& instruction);
        std::vector<Cube> Cut(const std::vector<Cube>& currentCubes, const Cube& instruction);
        std::vector<Cube> Cut(const Cube& existingCube, const Cube& cube);

        uint64_t Count(const std::vector<Cube>& currentRects);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif