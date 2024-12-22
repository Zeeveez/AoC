#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_set>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
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
        std::vector<char> map = {};

        std::pair<int, std::unordered_set<int>> GetStartAndPath(const std::vector<char>& map);
    };
}