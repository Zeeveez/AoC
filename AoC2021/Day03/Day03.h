#ifndef DAY03_H
#define DAY03_H

#include <cstdint>
#include <vector>
#include <string>
#include <iterator>
#include <chrono>

namespace AoC2021 {
    namespace Day03 {
        uint64_t CountValAtPos(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end, char val, size_t pos);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(std::vector<std::string> input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(std::vector<std::string> input);
    }
}
#endif