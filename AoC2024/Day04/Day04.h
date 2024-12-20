#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day04 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day04() : Day() {
            dayNo = 4;
            Load();
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::string> input = {};

        bool Check(int x, int y, int sx, int sy, std::string target);
    };
}