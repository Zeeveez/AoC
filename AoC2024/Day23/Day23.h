#pragma once
#include "../../AoC/Day/Day.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace AoC2024 {
    class Day23 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day23() : Day() {
            dayNo = 23;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::unordered_map<int, std::unordered_set<int>> map = {};

        std::string IDToString(int id);
    };
}