#ifndef DAY18_H
#define DAY18_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day18 {
        std::vector<std::pair<uint64_t, uint64_t>> PreProcessInput(const std::vector<std::string>& input);

        int Simulate(const std::vector<std::string>& input, int size, int simulate);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif