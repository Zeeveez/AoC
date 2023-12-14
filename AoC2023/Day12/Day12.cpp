#include "Day12.h"

#include <iostream>
#include <numeric>

namespace AoC2023::Day12 {
    SpringRow::SpringRow(const std::string& input, bool partB) {
        springs = {};
        damagedSpringGroups = {};

        for (size_t i = 0; i < (partB ? 5 : 1); i++) {
            int springGroup = 0;
            for (auto& c : input) {
                if (c == ' ') { continue; }
                if (c >= '0' && c <= '9') {
                    springGroup = springGroup * 10 + c - '0';
                }
                else if (c == ',') {
                    damagedSpringGroups.push_back(springGroup);
                    springGroup = 0;
                }
                else {
                    springs.push_back(c);
                }
            }
            damagedSpringGroups.push_back(springGroup);
        }
    }

    bool SpringRow::CheckValid(const std::vector<char>& springRow) {
        size_t currentGroupIdx = 0;
        size_t currentGroupLength = 0;
        for (size_t i = 0; i < springRow.size(); i++) {
            if (springRow[i] == '.') {
                if (currentGroupLength && currentGroupIdx >= damagedSpringGroups.size()) { return false; }
                if (currentGroupLength && currentGroupLength != damagedSpringGroups[currentGroupIdx++]) {
                    return false;
                }
                currentGroupLength = 0;
            }
            else {
                currentGroupLength++;
            }
        }

        return (currentGroupLength == 0 && currentGroupIdx == damagedSpringGroups.size())
            || (currentGroupIdx == damagedSpringGroups.size() - 1 && currentGroupLength == damagedSpringGroups[currentGroupIdx]);
    }

    size_t SpringRow::SpringPossibilityCount(std::vector<char>& springRow) {
        if (springRow.size() == springs.size()) {
            return CheckValid(springRow) ? 1 : 0;
        }

        if (springs[springRow.size()] == '?') {
            size_t res = 0;
            springRow.push_back('#');
            res += SpringPossibilityCount(springRow);
            springRow.pop_back();
            springRow.push_back('.');
            res += SpringPossibilityCount(springRow);
            springRow.pop_back();
            return res;
        }

        springRow.push_back(springs[springRow.size()]);
        size_t res = SpringPossibilityCount(springRow);
        springRow.pop_back();
        return res;
    }

    size_t SpringRow::SpringPossibilityCount() {
        std::vector<char> springRow = {};
        std::vector<char> springGroups = {};
        return SpringPossibilityCount(springRow);
    }

    std::vector<SpringRow> ParseInput(const std::vector<std::string>& input, bool partB) {
        std::vector<SpringRow> springs = {};
        for (auto& line : input) {
            springs.push_back(SpringRow(line, partB));
        }
        return springs;
    }


    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto springRows = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = 0;
        for (auto& springRow : springRows) {
            size_t res = springRow.SpringPossibilityCount();
            score += res;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto springRows = ParseInput(input, true);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = 0;
        for (auto& springRow : springRows) {
            size_t res = springRow.SpringPossibilityCount();
            score += res;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}