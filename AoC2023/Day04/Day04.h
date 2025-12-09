#pragma once
#include <vector>
#include <string>
#include <set>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day04 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day04() : Day() {
            dayNo = 4;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::pair<std::set<int>, std::set<int>>> cards = {};

        size_t GetWins(const std::pair<std::set<int>, std::set<int>>& card);
        std::pair<std::set<int>, std::set<int>> ParseCard(const std::string& card);
        std::vector<std::pair<std::set<int>, std::set<int>>> ParseInput(const std::vector<std::string>& input);
    };
}