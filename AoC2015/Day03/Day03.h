#pragma once
#include <string>
#include <unordered_map>
#include <functional>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
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
        std::string input = "";

        std::unordered_map<size_t, int> Solve(std::string input, std::function<bool(size_t)> indexCheck);
    };
}