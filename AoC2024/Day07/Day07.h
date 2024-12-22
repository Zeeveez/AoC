#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
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
        std::vector<std::string> input = {};
        std::vector<std::vector<uint64_t>> equations = {};

        bool Valid(const std::vector<uint64_t>& eq, bool withConcat = false);
        bool Valid(uint64_t solution, uint64_t current, const std::vector<uint64_t>& eq, int i = 0, bool withConcat = false);
        uint64_t Concat(uint64_t x, uint64_t y);
        uint64_t Run(bool withConcat = false);
    };
}