#include <cctype>

#include "Day06.h"

namespace AoC2025 {
    void Day06::Parse() {
        calculations = {};
        for (int i = 0; i < rawData[0].length(); i++) {
            if (rawData.back()[i] != ' ') {
                calculations.push_back({});
                // Push slot for number 
                for (int j = 0; j < rawData.size() - 1; j++) {
                    calculations.back().push_back({ });
                }
                // Push operator
                calculations.back().push_back({ rawData.back()[i] });
            }

            // Push digits for column
            for (int j = 0; j < rawData.size() - 1; j++) {
                calculations.back()[j].push_back(rawData[j][i]);
            }
        }
    }

    AoC::DayResult::PuzzleResult Day06::A() {
        std::uint64_t res = 0;

        for (auto& calculation : calculations) {
            std::uint64_t calcResult = 0;
            if (calculation.back()[0] == '*') { calcResult = 1; }

            for (int y = 0; y < calculation.size() - 1; y++) {
                std::uint64_t num = 0;
                for (int x = 0; x < calculation[0].size(); x++) {
                    if (calculation[y][x] == ' ') { continue; }
                    num = num * 10 + (calculation[y][x] - '0');
                }

                if (calculation.back()[0] == '*') {
                    calcResult *= num;
                }
                else {
                    calcResult += num;
                }
            }

            res += calcResult;
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day06::B() {
        std::uint64_t res = 0;

        for (auto& calculation : calculations) {
            std::uint64_t calcResult = 0;
            if (calculation.back()[0] == '*') { calcResult = 1; }

            for (int x = 0; x < calculation[0].size(); x++) {
                std::uint64_t num = 0;
                for (int y = 0; y < calculation.size() - 1; y++) {
                    if (calculation[y][x] == ' ') { continue; }
                    num = num * 10 + (calculation[y][x] - '0');
                }

                if (num == 0) { continue; }

                if (calculation.back()[0] == '*') {
                    calcResult *= num;
                }
                else {
                    calcResult += num;
                }
            }

            res += calcResult;
        }

        return res;
    }
}