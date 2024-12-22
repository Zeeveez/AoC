#pragma once
#include "../../AoC/Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day21 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day21() : Day() {
            dayNo = 21;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        uint64_t ShortestSequence(char pos, std::string sequence, int depth, int maxDepth);
    };
}