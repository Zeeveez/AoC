#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <set>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day12 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day12() : Day() {
            dayNo = 12;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        std::set<std::pair<int, int>> GetShape(int x, int y, std::set<std::pair<int, int>>& seen);
    };
}