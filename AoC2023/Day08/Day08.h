#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day08 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day08() : Day() {
            dayNo = 8;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::string instructions;
        std::unordered_map<int, std::pair<int, int>> paths = {};
    };
}