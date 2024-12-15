#ifndef DAY15_H
#define DAY15_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day15 {
        std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> PreProcessInputA(const std::vector<std::string>& input);
        std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> PreProcessInputB(const std::vector<std::string>& input);
        bool MoveA(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy);
        bool CanMove(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int> pos);
        void PushB(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int> pos);
        void MoveB(std::vector<std::vector<char>>& map, int dx, int dy, std::pair<int, int>& pos);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif