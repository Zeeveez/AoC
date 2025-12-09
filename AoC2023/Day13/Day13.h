#pragma once
#include <vector>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day13 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day13() : Day() {
            dayNo = 13;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::vector<std::vector<bool>>> grids = {};

        bool VerifyHorizontalReflection(const std::vector<std::vector<bool>>& grid, int checkCol, int row);
        int GetHorizontalReflection(const std::vector<std::vector<bool>>& grid);
        int GetHorizontalReflectionB(std::vector<std::vector<bool>>& grid);

        bool VerifyVerticalReflection(const std::vector<std::vector<bool>>& grid, int checkRow, int col);
        int GetVerticalReflection(const std::vector<std::vector<bool>>& grid);
        int GetVerticalReflectionB(std::vector<std::vector<bool>>& grid);
    };
}