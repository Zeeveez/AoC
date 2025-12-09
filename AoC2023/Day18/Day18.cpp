#include "Day18.h"

#include <iostream>
#include <regex>
#include <set>
#include <queue>

namespace AoC2023::Day18 {
    std::vector<std::tuple<std::pair<int, int>, int, std::pair<int, int>, int>> ParseInput(const std::vector<std::string>& input) {
        std::vector<std::tuple<std::pair<int, int>, int, std::pair<int, int>, int>> instrs = {};
        for (auto& line : input) {
            static const std::regex re("(\\w)\\s+(\\d+)\\s+\\(#([a-z0-9]{5})([a-z0-9]{1})\\)", std::regex::optimize);
            std::smatch sm;

            if (std::regex_search(line, sm, re)) {
                instrs.push_back(
                    {
                        {
                            sm[1] == 'R' ? 1 : (sm[1] == 'L' ? -1 : 0),
                            sm[1] == 'U' ? -1 : (sm[1] == 'D' ? 1 : 0)
                        },
                        std::stoi(sm[2]),
                        {
                            sm[4] == '0' ? 1 : (sm[4] == '2' ? -1 : 0),
                            sm[4] == '3' ? -1 : (sm[4] == '1' ? 1 : 0)
                        },
                        std::stoi(sm[3], nullptr, 16)
                    }
                );
            }
        }
        return instrs;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto instrs = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::set<std::pair<int, int>> lagoon = {};
        std::pair<int, int> pos = { 0, 0 };
        lagoon.insert(pos);

        for (const auto& instr : instrs) {
            for (size_t i = 0; i < std::get<1>(instr); i++) {
                pos.first += std::get<0>(instr).first;
                pos.second += std::get<0>(instr).second;
                lagoon.insert(pos);
            }
        }

        std::queue<std::pair<int, int>> queue = { };
        queue.push({ 1, 1 });

        while (!queue.empty()) {
            const auto& pos = queue.front(); queue.pop();
            if (lagoon.contains(pos)) { continue; }

            lagoon.insert(pos);
            queue.push({ pos.first + 1, pos.second });
            queue.push({ pos.first - 1, pos.second });
            queue.push({ pos.first, pos.second + 1 });
            queue.push({ pos.first, pos.second - 1 });
        }

        int64_t score = lagoon.size();

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto instrs = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::vector<std::pair<int64_t, int64_t>> points = {};
        std::pair<int64_t, int64_t> pos = { 0, 0 };

        for (const auto& instr : instrs) {
            pos.first += (int64_t)std::get<2>(instr).first * std::get<3>(instr);
            pos.second += (int64_t)std::get<2>(instr).second * std::get<3>(instr);
            points.push_back(pos);
        }

        // Shoelace algorithm
        int64_t sum1 = 0;
        int64_t sum2 = 0;
        for (size_t i = 0; i < points.size(); i++) {
            sum1 += points[i].first * points[(i + 1) % points.size()].second;
            sum2 += points[i].second * points[(i + 1) % points.size()].first;
        }

        int64_t score = std::abs(sum2 - sum1) / 2;

        int64_t length = 0;
        for (const auto& instr : instrs) {
            length += std::abs((int64_t)std::get<2>(instr).first * std::get<3>(instr));
            length += std::abs((int64_t)std::get<2>(instr).second * std::get<3>(instr));
        }

        // Pick's theorem
        score += length / 2 + 1;

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}