#ifndef DAY09_H
#define DAY09_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day09 {
        std::vector<std::pair<std::pair<int, int>, int>> PreProcessInput(const std::vector<std::string>& input);
        int HashPair(std::pair<int, int>& p);
        void Follow(std::pair<int, int>* head, std::pair<int, int>* tail);
        uint64_t Run(const std::vector<std::string>& input, int segments);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif