#ifndef DAY18_H
#define DAY18_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day18 {
        std::vector<std::pair<int, int>> PreProcessInput(const std::vector<std::string>& input);

        int Simulate(const std::vector<int>& memory, int size, int timePassed);
        std::vector<int> GetMemory(const std::vector<std::string>& input, int size);

        std::pair<int, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif