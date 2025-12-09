#ifndef DAY08_H
#define DAY08_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day08 {
        std::vector<std::pair<std::vector<int>, std::vector<int>>> PreProcessInput(const std::vector<std::string>& input);
        int CountBits(unsigned char input);
        std::pair<std::vector<int>, std::vector<int>> DecodeLine(const std::pair<std::vector<unsigned char>, std::vector<unsigned char>>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif