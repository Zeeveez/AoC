#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day05 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day05() : Day() {
            dayNo = 5;
            Load();
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::string> input = {};
        std::unordered_map<int, std::unordered_set<int>> whiteList = {};
        std::unordered_map<int, std::unordered_set<int>> blackList = {};
        std::vector<std::vector<int>> updates = {};
    };
}