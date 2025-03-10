#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day11 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day11() : Day() {
            dayNo = 11;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::unordered_map<int64_t, std::set<int64_t>> universe = {};

        uint64_t Solve(int64_t expansionAmount);
        std::pair<std::vector<int64_t>, std::vector<int64_t>> GetExpansionsPerDimension(int64_t width, int64_t height);
    };
}