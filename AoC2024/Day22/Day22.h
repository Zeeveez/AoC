#pragma once
#include "../../AoC/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day22 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day22() : Day() {
            dayNo = 22;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::uint32_t> input = {};

        uint32_t Step(uint32_t n);
    };
}