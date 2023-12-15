#include "Day12.h"

#include <iostream>
#include <numeric>
#include <regex>
#include <algorithm>

namespace AoC2023::Day12 {
    SpringRow::SpringRow(const std::string& input, bool partB) {
        auto baseSprings = input.substr(0, input.find(' '));
        auto baseCounts = input.substr(input.find(' ') + 1);

        std::string extendedSprings = "";
        std::string counts = "";

        for (size_t i = 0; i < (partB ? 5 : 1); i++) {
            extendedSprings += (i ? "?" : "") + baseSprings;
            counts += (i ? "," : "") + baseCounts;
        }

        damagedSpringGroups = {};

        for (auto& c : extendedSprings) {
            if (c == '.' && springs.length() && springs.back() == '.') {
                continue;
            }
            springs.push_back(c);
        }

        std::string::const_iterator countSearch(counts.cbegin());
        static const std::regex countRe("(\\d+)", std::regex::optimize);
        std::smatch countMatch;
        while (std::regex_search(countSearch, counts.cend(), countMatch, countRe)) {
            damagedSpringGroups.push_back(std::stoi(countMatch[1]));
            countSearch = countMatch.suffix().first;
        }
    }

    size_t SpringRow::CountPossibilities(size_t pos, size_t currentGroupIdx, size_t toFit) {
        // Memoization
        if (cache.contains({ pos, currentGroupIdx })) {
            return cache[{pos, currentGroupIdx}];
        }

        // Captured all groups, check if valid
        if (currentGroupIdx == damagedSpringGroups.size()) {
            for (size_t i = pos; i < springs.length(); i++) {
                if (springs[i] == '#') {
                    cache[{pos, currentGroupIdx}] = 0;
                    return 0;
                }
            }
            cache[{pos, currentGroupIdx}] = 1;
            return 1;
        }

        // End of string
        if (pos >= springs.size()) {
            cache[{pos, currentGroupIdx}] = 0;
            return 0;
        }

        // No way to fit groups
        if (springs.size() - pos < toFit) {
            cache[{pos, currentGroupIdx}] = 0;
            return 0;
        }

        // Skip gaps
        if (springs[pos] == '.') {
            cache[{pos, currentGroupIdx}] = CountPossibilities(pos + 1, currentGroupIdx, toFit);
            return cache[{pos, currentGroupIdx}];
        }

        // Forced group position
        if (springs[pos] == '#') {
            // Spring group doesn't end at expected position
            if (springs[pos + damagedSpringGroups[currentGroupIdx]] == '#') {
                cache[{pos, currentGroupIdx}] = 0;
                return 0;
            }

            for (size_t offset = 1; offset < damagedSpringGroups[currentGroupIdx]; offset++) {
                if (springs[pos + offset] == '.') {
                    cache[{pos, currentGroupIdx}] = 0;
                    return 0;
                }
            }

            cache[{pos, currentGroupIdx}] = CountPossibilities(pos + damagedSpringGroups[currentGroupIdx] + 1, currentGroupIdx + 1, toFit - damagedSpringGroups[currentGroupIdx] - 1);
            return cache[{pos, currentGroupIdx}];
        }
        else {
            size_t res = 0;
            // Try #
            bool shouldTry = true;
            if (springs[pos + damagedSpringGroups[currentGroupIdx]] == '#') {
                shouldTry = false;
            }
            if (shouldTry) {
                for (size_t offset = 1; offset < damagedSpringGroups[currentGroupIdx]; offset++) {
                    if (springs[pos + offset] == '.') {
                        shouldTry = false;
                        break;
                    }
                }
            }
            if (shouldTry) {
                res += CountPossibilities(pos + damagedSpringGroups[currentGroupIdx] + 1, currentGroupIdx + 1, toFit - damagedSpringGroups[currentGroupIdx] - 1);
            }


            // Try .
            res += CountPossibilities(pos + 1, currentGroupIdx, toFit);

            cache[{pos, currentGroupIdx}] = res;
            return res;
        }
    }

    size_t SpringRow::CountPossibilities() {
        size_t toFit = 0;
        for (size_t i = 0; i < damagedSpringGroups.size(); i++) {
            toFit += damagedSpringGroups[i];
        }
        toFit += damagedSpringGroups.size() - 1;
        return CountPossibilities(0, 0, toFit);
    }

    std::vector<SpringRow> ParseInput(const std::vector<std::string>& input, bool partB) {
        std::vector<SpringRow> springs = {};
        for (auto& line : input) {
            springs.push_back(SpringRow(line, partB));
        }
        return springs;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> Solve(const std::vector<std::string>& input, bool partB) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto springRows = ParseInput(input, partB);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = 0;
        for (auto& springRow : springRows) {
            score += springRow.CountPossibilities();
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        return Solve(input);
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        return Solve(input, true);
    }
}