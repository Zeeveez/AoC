#pragma once
#include <vector>
#include <cstdint>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day02 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day02(int dayNo) : Day(dayNo) {
            Load();
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::vector<uint64_t>> input = {};

        bool IsSafe(const std::vector<uint64_t>& line, int ignoreIdx = -1);
    };
}