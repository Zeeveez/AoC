#ifndef DAY02_H
#define DAY02_H

#include <unordered_map>
#include <cstdint>
#include <vector>
#include <chrono>

namespace AoC2022 {
    namespace Day02 {
        enum Shapes {
            ROCK,
            PAPER,
            SCISSORS
        };
        enum Outcomes {
            LOSE,
            DRAW,
            WIN
        };

        static std::unordered_map<char, Shapes> SHAPE_MAPPINGS = {
            { 'A', ROCK },
            { 'B', PAPER },
            { 'C', SCISSORS },
            { 'X', ROCK },
            { 'Y', PAPER },
            { 'Z', SCISSORS }
        };

        static std::unordered_map<char, Outcomes> OUTCOME_MAPPINGS = {
            { 'X', LOSE },
            { 'Y', DRAW },
            { 'Z', WIN }
        };

        static std::unordered_map<Shapes, int> SHAPE_SCORE = {
            { ROCK, 1 },
            { PAPER, 2 },
            { SCISSORS, 3 },
        };
        static std::unordered_map<Shapes, std::unordered_map<Shapes, int>> MATCH_SCORE = {
            { ROCK, {
                { ROCK, 3 },
                { PAPER, 0 },
                { SCISSORS, 6 }
            } },
            { PAPER, {
                { ROCK, 6 },
                { PAPER, 3 },
                { SCISSORS, 0 }
            } },
            { SCISSORS, {
                { ROCK, 0 },
                { PAPER, 6 },
                { SCISSORS, 3 }
            } }
        };

        static std::unordered_map<Outcomes, std::unordered_map<Shapes, Shapes>> MATCH_FIXING_SHAPE = {
            { LOSE, {
                { ROCK, SCISSORS },
                { PAPER, ROCK },
                { SCISSORS, PAPER }
            } },
            { DRAW, {
                { ROCK, ROCK },
                { PAPER, PAPER },
                { SCISSORS, SCISSORS }
            } },
            { WIN, {
                { ROCK, PAPER },
                { PAPER, SCISSORS },
                { SCISSORS, ROCK }
            } }
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<char>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<char>& input);
    }
}
#endif