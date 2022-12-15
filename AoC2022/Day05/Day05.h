#ifndef DAY05_H
#define DAY05_H

#include <cstdint>
#include <vector>
#include <deque>
#include <tuple>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day05 {
        std::pair<std::vector<std::deque<char>>, std::vector<std::tuple<int, int, int>>> PreProcessInput(const std::vector<std::string>& lines);
        std::pair<std::string, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif