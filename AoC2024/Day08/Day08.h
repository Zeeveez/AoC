#ifndef DAY08_H
#define DAY08_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <functional>

namespace AoC2024 {
    namespace Day08 {
        std::unordered_map<char, std::vector<std::pair<int, int>>> GetNodes(const std::vector<std::string>& input);
        void AddAntinodesA(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid);
        void AddAntinodesB(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid);
        uint64_t CountAntinodes(const std::vector<std::string>& grid);
        uint64_t Run(std::vector<std::string> input, std::function<void(std::pair<int, int> a, std::pair<int, int> b, std::vector<std::string>& grid)> antinodeFunc);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif