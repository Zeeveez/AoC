#pragma once
#include <vector>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day02 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day02() : Day() {
            dayNo = 2;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::vector<uint64_t>> input = {};

        bool IsSafe(const std::vector<uint64_t>& line, int ignoreIdx = -1);
    };
}