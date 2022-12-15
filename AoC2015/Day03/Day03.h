#ifndef DAY03_H
#define DAY03_H

#include <functional>
#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day03 {
        std::unordered_map<size_t, int> Solve(std::string input, std::function<bool(size_t)> indexCheck);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(std::string input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(std::string input);
    }
}
#endif