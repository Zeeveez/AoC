#pragma once
#include "../Day/Day.h"

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
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::string> input = {};
    };
}