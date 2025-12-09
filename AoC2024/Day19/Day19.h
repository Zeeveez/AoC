#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <map>

#include "../../Shared/Day/Day.h"

namespace AoC2024 {
    class Day19 : public AoC::Day<std::vector<std::string>, 2024, 19> {
    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::vector<std::string> patterns = {};
        std::vector<std::string> designs = {};

        bool IsValid(const std::string& design, size_t i);
        uint64_t CountValid(std::map<std::string, uint64_t>& memory, const std::string& design, size_t i);
    };
}