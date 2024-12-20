#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>
#include <set>

#include "../Day/Day.h"

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
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::string> input = {};

        std::set<std::pair<int, int>> GetShape(int x, int y, std::set<std::pair<int, int>>& seen);
    };
}