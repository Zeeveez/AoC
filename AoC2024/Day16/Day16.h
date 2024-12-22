#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day16 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day16() : Day() {
            dayNo = 16;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>> testCases = {};

        std::pair<uint64_t, uint64_t> Run();
        void BestPath(int size, int x, int y, int dx, int dy, std::vector<int>& seen, std::vector<uint64_t>& scoresToTiles, uint64_t score, uint64_t& bestScore, std::vector<uint64_t>& tilePathScores);
    };
}