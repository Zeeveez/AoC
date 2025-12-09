#include <cstdint>

#include "Day14.h"

namespace AoC2019 {
    void Day14::Parse() {
        formulae = {};

        for (auto& line : rawData) {
            std::vector<std::pair<int, std::string>> ingredients;
            std::string currentIngredient = "";
            int currentIngredientCount = 0;

            for (auto& c : line) {
                if (c >= '0' && c <= '9') {
                    currentIngredientCount = currentIngredientCount * 10 + c - '0';
                }
                else if (c >= 'A' && c <= 'Z') {
                    currentIngredient += c;
                }
                else if (c == ',' || c == '=') {
                    ingredients.push_back({ currentIngredientCount, currentIngredient });
                    currentIngredient = "";
                    currentIngredientCount = 0;
                }
            }
            formulae[currentIngredient] = { currentIngredientCount, ingredients };
        }
    }

    AoC::DayResult::PuzzleResult Day14::A() {
        std::map<std::string, int> needs = { {"FUEL",1}, {"ORE",0} };
        while (true) {
            for (auto& need : needs) {
                if (need.first != "ORE") {
                    int needCount = need.second;
                    while (need.second > 0) {
                        need.second -= formulae[need.first].first;
                        for (auto& output : formulae[need.first].second) {
                            if (needs.count(output.second) == 0) {
                                needs[output.second] = output.first;
                            }
                            else {
                                needs[output.second] += output.first;
                            }
                        }
                    }
                }
            }
            bool done = true;
            for (auto& need : needs) {
                if (need.first != "ORE") {
                    if (need.second > 0) {
                        done = false;
                    }
                }
            }
            if (done) { break; }
        }
        return needs["ORE"];
    }

    AoC::DayResult::PuzzleResult Day14::B() {
        std::map<std::string, std::int64_t> needs = { {"FUEL",1}, {"ORE",0} };
        std::int64_t fuel = 1;
        std::int64_t roughOrePerFuel = 0;
        while (true) {
            for (auto& need : needs) {
                if (need.first != "ORE") {
                    std::int64_t needCount = need.second;
                    std::int64_t useCount = 0;
                    useCount = need.second / formulae[need.first].first;
                    need.second -= useCount * formulae[need.first].first;
                    if (need.second > 0) {
                        useCount++;
                        need.second -= formulae[need.first].first;
                    }
                    for (auto& output : formulae[need.first].second) {
                        if (needs.count(output.second) == 0) {
                            needs[output.second] = output.first * useCount;
                        }
                        else {
                            needs[output.second] += output.first * useCount;
                        }
                    }
                }
            }
            bool done = true;
            for (auto& need : needs) {
                if (need.first != "ORE") {
                    if (need.second > 0) {
                        done = false;
                    }
                }
            }
            if (done) {
                if (fuel == 1) {
                    roughOrePerFuel = needs["ORE"];
                }
                if (needs["ORE"] < 1000000000000) {
                    std::int64_t oreRemaining = 1000000000000 - needs["ORE"];
                    if (oreRemaining > roughOrePerFuel * 100) {
                        needs["FUEL"] += (oreRemaining / roughOrePerFuel) - 100 + 1;
                        fuel += (oreRemaining / roughOrePerFuel) - 100 + 1;
                    }
                    else {
                        needs["FUEL"]++;
                        fuel++;
                    }
                }
                else {
                    break;
                }
            }
        }
        return fuel - 1;
    }
}