#include "Day01.h"

#include <algorithm>

namespace AoC2023 {
    namespace Day01 {
        std::vector<uint64_t> GetDigits(const std::string& input, bool includeWords) {
            std::vector<uint64_t> digits = {};

            for (size_t i = 0; i < input.length(); i++) {
                if (input[i] >= '0' && input[i] <= '9') {
                    digits.push_back(input[i] - '0');
                }

                if (includeWords) {
                    if (input.substr(i, 3) == "one") { digits.push_back(1); }
                    else if (input.substr(i, 3) == "two") { digits.push_back(2); }
                    else if (input.substr(i, 5) == "three") { digits.push_back(3); }
                    else if (input.substr(i, 4) == "four") { digits.push_back(4); }
                    else if (input.substr(i, 4) == "five") { digits.push_back(5); }
                    else if (input.substr(i, 3) == "six") { digits.push_back(6); }
                    else if (input.substr(i, 5) == "seven") { digits.push_back(7); }
                    else if (input.substr(i, 5) == "eight") { digits.push_back(8); }
                    else if (input.substr(i, 4) == "nine") { digits.push_back(9); }
                }
            }

            return digits;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t s = 0;
            for (auto& l : input) {
                auto digits = GetDigits(l);
                s += digits[0] * 10 + digits[digits.size() - 1];
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { s, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t s = 0;
            for (auto& l : input) {
                auto digits = GetDigits(l, true);
                s += digits[0] * 10 + digits[digits.size() - 1];
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { s, endTime - startTime };
        }
    }
}