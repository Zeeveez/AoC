#ifndef DAY14_H
#define DAY14_H

#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

namespace AoC2015 {
    namespace Day14 {
        std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input, int iter = 10);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}

#endif