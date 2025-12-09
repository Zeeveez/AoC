#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
    class Day06 : public AoC::Day {
    private:
        enum class InstructionType {
            ON,
            OFF,
            TOGGLE
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day06() : Day() {
            dayNo = 6;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::tuple<InstructionType, int, int, int, int>> instructions = {};
    };
}