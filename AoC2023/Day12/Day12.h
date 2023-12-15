#ifndef DAY12_H
#define DAY12_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <map>

namespace AoC2023::Day12 {
    class SpringRow {
    public:
        std::map<std::pair<size_t,size_t>, size_t> cache;
        std::string springs;
        std::vector<int> damagedSpringGroups;

        SpringRow() = default;
        SpringRow(const std::string& input, bool partB = false);

        size_t CountPossibilities(size_t pos, size_t currentGroupIdx, size_t toFit);
        size_t CountPossibilities();

        //bool CheckValid(const std::vector<char>& springRow);
        //size_t SpringPossibilityCount(std::vector<char>& springRow);
        //size_t SpringPossibilityCount();
    };

    std::vector<SpringRow> ParseInput(const std::vector<std::string>& input, bool partB = false);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif