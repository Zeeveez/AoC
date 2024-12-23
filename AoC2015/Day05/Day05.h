#pragma once
#include <vector>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
    class Day05 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day05() : Day() {
            dayNo = 5;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        inline bool VowelTest(const std::string& s);
        inline bool DoubleTest(const std::string& s);
        inline bool BadPairTest(const std::string& s);
        inline bool DoublePairTest(const std::string& s);
        inline bool DoubleGapTest(const std::string& s);
    };
}