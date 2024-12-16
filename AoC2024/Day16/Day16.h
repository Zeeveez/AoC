#ifndef DAY16_H
#define DAY16_H

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day16 {
        std::tuple<int, int, int, int> GetStartAndEnd(const std::vector<std::string>& input);
        void BestPath(const std::vector<std::string>& input, int x, int y, int dx, int dy, int tx, int ty, std::vector<int>& seen, std::vector<std::vector<uint64_t>>& scoresToTiles, uint64_t score, uint64_t& bestScore, std::vector<uint64_t>& tileScores);
        std::pair<uint64_t, uint64_t> Run(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif