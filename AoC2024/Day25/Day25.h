#pragma once
#include "../Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day25 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day25() : Day() {
            dayNo = 25;
            Load();
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::string> input = {};
    };
}