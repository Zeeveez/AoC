#ifndef DAY20_H
#define DAY20_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>

namespace AoC2022 {
    namespace Day20 {
        std::pair<std::unordered_map<int64_t, int64_t>, std::vector<int64_t>> PreProcessInput(const std::vector<int>& input);

        int GetResult(const std::unordered_map<int64_t, int64_t>& indexMappings, const std::vector<int64_t>& indices);

        void MoveItem(std::vector<int64_t>& list, int64_t item, int64_t moves);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input);
    }
}
#endif