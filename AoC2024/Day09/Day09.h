#pragma once
#include <string>
#include <cstdint>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day09 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day09() : Day() {
            dayNo = 9;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::string input = {};
    };
}