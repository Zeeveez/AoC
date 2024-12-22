#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day03 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day03() : Day() {
            dayNo = 3;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::tuple<std::string, int, int>> instructions = {};
    };
}