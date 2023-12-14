#ifndef DAY02_H
#define DAY02_H

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <chrono>

namespace AoC2023::Day02 {
    enum class Color {
        RED,
        GREEN,
        BLUE
    };

    std::pair<Color, int> ParseDraw(const std::string& line, size_t& i);
    std::unordered_map<Color, int> ParseRound(const std::string& line, size_t& i);
    std::vector<std::unordered_map<Color, int>> ParseGame(const std::string& line);
    std::vector<std::vector<std::unordered_map<Color, int>>> ParseInput(const std::vector<std::string>& input);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif