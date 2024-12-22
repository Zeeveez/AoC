#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day10 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day10() : Day() {
            dayNo = 10;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        int Traverse(const std::vector<std::string>& input, int startX, int startY, bool uniquePeaksOnly = true);
    };
}