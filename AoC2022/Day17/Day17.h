#ifndef DAY17_H
#define DAY17_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <functional>

namespace AoC2022 {
    namespace Day17 {
        typedef std::function<bool(int x, int y, std::vector<std::vector<bool>>& grid)> rockFunc;
        class Rock {
        public:
            rockFunc leftCollision;
            rockFunc rightCollision;
            rockFunc downCollision;
            rockFunc place;
            int height;

            Rock(rockFunc leftCollision, rockFunc rightCollision, rockFunc downCollision, rockFunc place, int height) : leftCollision(leftCollision), rightCollision(rightCollision), downCollision(downCollision), place(place), height(height) {}
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<char>& input, int rockCount = 2022);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<char>& input);
    }
}
#endif