#pragma once
#include <string>
#include <cstdint>
#include <functional>
#include <tuple>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
    class Day04 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day04() : Day() {
            dayNo = 4;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::string input = "";

        uint64_t Test(std::string, std::function<bool(std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>)> validityCheck);
    };
}