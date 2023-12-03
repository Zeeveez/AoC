#ifndef DAY03_H
#define DAY03_H

#include <cstdint>
#include <map>
#include <vector>
#include <chrono>

namespace AoC2023 {
    namespace Day03 {
        std::vector<std::pair<size_t, size_t>> GetNeighbours(size_t x, size_t y, const std::vector<std::string>& input);
        void RegisterPartNo(std::map<std::pair<size_t, size_t>, std::vector<int>>& partNoLists, char partType, std::pair<size_t, size_t> partPos, size_t partNo);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif