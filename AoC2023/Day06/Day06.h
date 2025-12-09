#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day06 : public AoC::Day {
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

        std::vector<uint64_t> ParseLine(const std::string& input, bool partB = false);
        std::vector<std::pair<uint64_t, uint64_t>> ParseInput(const std::vector<std::string>& input, bool partB = false);
        uint64_t CountWins(uint64_t time, uint64_t record);
    };
}