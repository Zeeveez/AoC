#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day17 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day17() : Day() {
            dayNo = 17;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<uint64_t> registers = {};
        std::vector<int> program = {};

        int Tick(std::vector<uint64_t>& regs, int& ip);
        std::pair<std::vector<uint64_t>, std::vector<uint64_t>> ExtractCycle(std::vector<uint64_t>& maybeCycle);
        std::pair<std::vector<uint64_t>, std::vector<uint64_t>> FindCycle(std::vector<uint64_t> state, int progTarget, uint64_t initA, std::vector<uint64_t>& increments);
    };
}