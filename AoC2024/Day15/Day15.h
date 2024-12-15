#ifndef DAY15_H
#define DAY15_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <functional>

namespace AoC2024 {
    namespace Day15 {
        std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> PreProcessInputA(const std::vector<std::string>& input);
        std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>> PreProcessInputB(const std::vector<std::string>& input);
        
        bool MoveA(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool _);
        bool MoveB(std::vector<std::vector<char>>& map, int x, int y, int dx, int dy, bool yMoveTest);
        
        uint64_t Score(std::vector<std::vector<char>>& map, char target);

        uint64_t Run(
            std::function<std::tuple<std::vector<std::vector<char>>, std::string, std::pair<int, int>>(const std::vector<std::string>& input)> parseFunc,
            std::function<bool(std::vector<std::vector<char>>&, int, int, int, int, bool)> moveFunc,
            const std::vector<std::string>& input,
            char target
        );
        
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif