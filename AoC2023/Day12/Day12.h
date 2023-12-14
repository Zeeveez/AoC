#ifndef DAY12_H
#define DAY12_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2023::Day12 {
    class SpringRow {
    public:
        std::vector<char> springs;
        std::vector<int> damagedSpringGroups;

        SpringRow() = default;
        SpringRow(const std::string& input, bool partB = false);

        bool CheckValid(const std::vector<char>& springRow);
        size_t SpringPossibilityCount(std::vector<char>& springRow);
        size_t SpringPossibilityCount();
    };

    std::vector<SpringRow> ParseInput(const std::vector<std::string>& input, bool partB = false);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif