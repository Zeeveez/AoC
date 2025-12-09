#pragma once
#include <vector>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day17 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day17() : Day() {
            dayNo = 17;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::vector<int>> grid = {};
    };
}