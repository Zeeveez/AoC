#pragma once
#include <vector>
#include <string>
#include <map>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day03 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day03() : Day() {
            dayNo = 3;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::map<std::pair<size_t, size_t>, std::vector<int>> partNoLists = {};

        std::vector<std::pair<size_t, size_t>> GetNeighbours(size_t x, size_t y, const std::vector<std::string>& input);
        void RegisterPartNo(std::map<std::pair<size_t, size_t>, std::vector<int>>& partNoLists, char partType, std::pair<size_t, size_t> partPos, size_t partNo);
        std::map<std::pair<size_t, size_t>, std::vector<int>> GetPartNumberLists(const std::vector<std::string>& input);
    };
}