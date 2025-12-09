#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day17 : public AoC::Day<std::vector<std::string>, 2024, 17> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<uint64_t> registers = {};
        std::vector<int> program = {};

        int Tick(std::vector<uint64_t>& regs, int& ip);
        std::pair<std::vector<uint64_t>, std::vector<uint64_t>> ExtractCycle(std::vector<uint64_t>& maybeCycle);
        std::pair<std::vector<uint64_t>, std::vector<uint64_t>> FindCycle(std::vector<uint64_t> state, int progTarget, uint64_t initA, std::vector<uint64_t>& increments);
    };
}