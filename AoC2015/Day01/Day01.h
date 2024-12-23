#pragma once
#include "../../AoC/Day/Day.h"

namespace AoC2015 {
    class Day01 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day01() : Day() {
            dayNo = 1;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::string input = "";
    };
}