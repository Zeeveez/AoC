#ifndef DAY04_H
#define DAY04_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day04 {
        std::pair<std::pair<int, int>, std::pair<int, int>> PreProcessLine(const std::string& line);
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PreProcessLines(const std::vector<std::string>& lines);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif