#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>
#include <functional>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day08 : public AoC::Day<std::vector<std::string>, 2024, 8> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::unordered_map<char, std::vector<std::pair<int, int>>> nodes = {};

        static void AddAntinodesA(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid);
        static void AddAntinodesB(const std::pair<int, int>& a, const std::pair<int, int>& b, std::vector<std::string>& grid);
        uint64_t CountAntinodes(const std::vector<std::string>& grid);
        uint64_t RunSolution(std::function<void(const std::pair<int, int>&, const std::pair<int, int>&, std::vector<std::string>&)> antinodeFunc);
    };
}