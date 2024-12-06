#ifndef DAY12_H
#define DAY12_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <set>
#include <unordered_map>

namespace AoC2022 {
    namespace Day12 {
        std::vector<std::vector<char>> PreProcessInput(const std::vector<std::string>& input);
        int HashPair(std::pair<int, int> p);
        std::pair<int, int> GetStartAndEnd(std::vector<std::vector<char>> grid);
        std::set<int> GetExtraStarts(std::vector<std::vector<char>> grid);
        std::unordered_map<int, std::vector<int>> GenerateGraph(const std::vector<std::vector<char>>& grid);
        std::unordered_map<int, std::vector<int>> GenerateReverseGraph(const std::vector<std::vector<char>>& grid);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif