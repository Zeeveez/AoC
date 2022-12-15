#ifndef DAY10_H
#define DAY10_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day10 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif