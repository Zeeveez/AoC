#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
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
        std::vector<std::string> input = {};

        std::tuple<uint64_t, uint64_t, uint64_t> ReadBox(std::string str);
    };
}