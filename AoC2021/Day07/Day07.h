#pragma once
#include <vector>
#include <cstdint>
#include <functional>

#include "../../AoC/Day/Day.h"

namespace AoC2021 {
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
        std::vector<int64_t> input = {};

        uint64_t Run(const std::vector<int64_t>& input, const std::function<int64_t(int64_t, int64_t)>& accFunc);
    };
}