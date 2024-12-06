#ifndef DAY03_H
#define DAY03_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day03 {
        std::vector<std::tuple<std::string, int, int>> PreProcessInput(const std::vector<std::string>& input);

        uint64_t ProcessA(const std::vector<std::string>& input);
        uint64_t ProcessB(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif