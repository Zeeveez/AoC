#ifndef DAY18_H
#define DAY18_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day18 {
        enum class State {
            EMPTY,
            POPULATED,
            CHECKED
        };
        std::vector<std::vector<std::vector<State>>> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif