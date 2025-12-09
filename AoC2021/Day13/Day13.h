#ifndef DAY13_H
#define DAY13_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day13 {
        std::pair<std::vector<std::vector<bool>>, std::vector<std::pair<char, int>>> PreProcessInput(const std::vector<std::string>& input);

        void Fold(std::vector<std::vector<bool>>& paper, std::pair<int, int>& widthHeight, const std::pair<char, int>& instruction);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}

#endif