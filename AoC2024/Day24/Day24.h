#pragma once
#include "../../AoC/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day24 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day24() : Day() {
            dayNo = 24;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
    };
}