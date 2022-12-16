#ifndef DAY06_H
#define DAY06_H

#include <vector>
#include <string>
#include <cstdint>
#include <chrono>

namespace AoC2015 {
    namespace Day06 {
        enum class Instruction {
            ON,
            OFF,
            TOGGLE
        };
        std::vector<std::tuple<Instruction, int, int, int, int>> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif