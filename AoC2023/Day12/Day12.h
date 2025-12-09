#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day12 : public AoC::Day {
    private:
        class SpringRow {
        public:
            std::vector<size_t> cache;
            std::string springs;
            std::vector<int> damagedSpringGroups;

            SpringRow() = default;
            SpringRow(const std::string& input, bool partB = false);

            size_t CountPossibilities(size_t pos, size_t currentGroupIdx, size_t toFit);
            size_t CountPossibilities();
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day12() : Day() {
            dayNo = 12;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        uint64_t Solve(bool partB = false);
    };
}