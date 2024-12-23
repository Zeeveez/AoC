#pragma once
#include <vector>
#include <cstdint>
#include <functional>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
    class Day07 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day07() : Day() {
            dayNo = 7;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<int> input = {};

        uint64_t Run(const std::vector<int>& input, const std::function<int(int, int)>& accFunc);
    };
}