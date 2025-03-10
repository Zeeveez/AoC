#pragma once
#include <vector>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day14 : public AoC::Day {
    private:
        enum Tile {
            ROUND,
            CUBE,
            EMPTY
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day14() : Day() {
            dayNo = 14;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        std::vector<std::vector<Tile>> MakeGrid();
        void Tilt(std::vector<std::vector<Tile>>& grid, std::pair<int, int> dir);
        void Cycle(std::vector<std::vector<Tile>>& grid);
    };
}