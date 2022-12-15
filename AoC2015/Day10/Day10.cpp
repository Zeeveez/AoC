#include "Day10.h"

#include <unordered_map>
#include <stack>
#include <algorithm>

namespace AoC2015 {
    namespace Day10 {
        const std::unordered_map<char, char> BRACKET_PAIRS = {
            { '(', ')' },
            { '[', ']' },
            { '{', '}' },
            { '<', '>' }
        };
        const std::unordered_map<char, int> BRACKET_SCORES = {
            { '(', 1 },
            { '[', 2 },
            { '{', 3 },
            { '<', 4 },
            { ')', 3 },
            { ']', 57 },
            { '}', 1197 },
            { '>', 25137 }
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            uint64_t score = 0;
            for (auto& line : input) {
                std::stack<char> stack = { };
                for (auto& c : line) {
                    if (BRACKET_PAIRS.contains(c)) {
                        stack.push(c);
                    }
                    else {
                        if (stack.size() == 0 || BRACKET_PAIRS.at(stack.top()) != c) {
                            score += BRACKET_SCORES.at(c);
                            break;
                        }
                        stack.pop();
                    }
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            std::vector<uint64_t> scores = {};
            for (auto& line : input) {
                std::stack<char> stack = { };
                bool valid = true;
                for (auto& c : line) {
                    if (BRACKET_PAIRS.contains(c)) {
                        stack.push(c);
                    }
                    else {
                        if (stack.size() == 0 || BRACKET_PAIRS.at(stack.top()) != c) {
                            valid = false;
                            break;
                        }
                        stack.pop();
                    }
                }
                if (valid) {
                    uint64_t score = 0;
                    while (stack.size()) {
                        score = score * 5 + BRACKET_SCORES.at(stack.top());
                        stack.pop();
                    }
                    scores.push_back(score);
                }
            }
            std::sort(scores.begin(), scores.end());
            auto endTime = std::chrono::high_resolution_clock::now();
            return { scores[scores.size() / 2], endTime - startTime };
        }
    }
}