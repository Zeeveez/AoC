#pragma once
#include <vector>
#include <string>
#include <set>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day10 : public AoC::Day {
    private:
        enum class Pipe {
            UP_DOWN,
            LEFT_RIGHT,
            UP_RIGHT,
            UP_LEFT,
            DOWN_LEFT,
            DOWN_RIGHT,
            GROUND,
            START
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day10() : Day() {
            dayNo = 10;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::vector<Pipe>> grid = {};

        size_t InflateAndFillGrid();

        std::pair<size_t, size_t> FindStart();

        std::vector<std::pair<size_t, size_t>> GetPathNeighbours(const std::pair<size_t, size_t>& pos);
        std::vector<std::pair<size_t, size_t>> GetAllNeighbours(const std::vector<std::vector<int>>& grid, const std::pair<size_t, size_t>& pos);

        std::set<std::pair<size_t, size_t>> FindPath(const std::pair<size_t, size_t>& pos);
    };
}