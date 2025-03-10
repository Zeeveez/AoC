#pragma once
#include <vector>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day15 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day15() : Day() {
            dayNo = 15;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::string input;
        std::vector<std::string> strings = {};

        size_t Hash(std::string str);
    };
}