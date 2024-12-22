#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day18 : public AoC::Day {
    private:
        std::vector<std::pair<int, int>> dirs = {
            { 0, 1 },
            { 0, -1 },
            { -1, 0 },
            { 1, 0 },
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day18() : Day() {
            dayNo = 18;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::pair<int, int>> coords = {};
        std::vector<int> memory = {};

        uint64_t Simulate(int size, int timePassed);
    };
}