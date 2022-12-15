#ifndef DAY21_H
#define DAY21_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day21 {
        std::pair<int, int> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif