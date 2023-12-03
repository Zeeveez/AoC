#ifndef DAY22_H
#define DAY22_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day22 {
        enum State {
            FLOOR,
            WALL,
            VOID
        };

        struct Instruction {
        public:
            bool isMove = true;
            int moveCount = 0;
            char dir = 'L';
            Instruction(int moveCount) : isMove(true), moveCount(moveCount) {}
            Instruction(char dir) : isMove(false), dir(dir) {}
        };

        std::pair<std::vector<std::vector<State>>, std::vector<Instruction>> PreProcessInput(const std::vector<std::string>& input);
        std::pair<int, int> Move(const std::vector<std::vector<State>>& map, std::pair<int, int> pos, std::pair<int, int> dir);
        std::pair<std::pair<int, int>, std::pair<int, int>> CubeMove(const std::vector<std::vector<State>>& map, std::pair<int, int> pos, std::pair<int, int> dir);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif