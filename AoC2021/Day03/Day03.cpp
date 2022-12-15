#include "Day03.h"

#include <algorithm>

namespace AoC2021 {
    namespace Day03 {
        uint64_t CountValAtPos(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end, char val, size_t pos) {
            uint64_t c = 0;
            for (auto it = begin; it != end; it++) {
                c += (*it)[pos] == val;
            }
            return c;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(std::vector<std::string> input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            uint64_t gammaRate = 0;
            uint64_t epsilonRate = 0;
            for (size_t i = 0; i < input[0].size(); i++) {
                bool mostlyOnes = CountValAtPos(input.begin(), input.end(), '1', input[0].size() - i - 1) > std::distance(input.begin(), input.end()) / 2.0;
                gammaRate |= (mostlyOnes ? 1ull : 0) << i;
                epsilonRate |= (!mostlyOnes ? 1ull : 0) << i;
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { gammaRate * epsilonRate, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(std::vector<std::string> input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            std::string o2genRating = "";
            std::string co2scrubRating = "";

            for (size_t i = 0; i < input[0].size(); i++) {
                auto endOfGoodValues = std::partition(
                    input.begin(), input.end(),
                    [o2genRating](const std::string& x) {
                        return x.rfind(o2genRating, 0) == 0;
                    }
                );
                if (std::distance(input.begin(), endOfGoodValues) <= 1) {
                    o2genRating = input[0];
                }
                else {
                    bool mostlyOnes = CountValAtPos(input.begin(), endOfGoodValues, '1', i) >= std::distance(input.begin(), endOfGoodValues) / 2.0;
                    o2genRating = o2genRating + (mostlyOnes ? "1" : "0");
                }

                endOfGoodValues = std::partition(
                    input.begin(), input.end(),
                    [co2scrubRating](const std::string& x) {
                        return x.rfind(co2scrubRating, 0) == 0;
                    }
                );
                if (std::distance(input.begin(), endOfGoodValues) <= 1) {
                    co2scrubRating = input[0];
                }
                else {
                    bool mostlyOnes = CountValAtPos(input.begin(), endOfGoodValues, '0', i) <= std::distance(input.begin(), endOfGoodValues) / 2.0;
                    co2scrubRating = co2scrubRating + (mostlyOnes ? "0" : "1");
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();

            return { std::stoull(o2genRating, nullptr, 2) * std::stoull(co2scrubRating, nullptr, 2), endTime - startTime };
        }
    }
}