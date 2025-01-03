#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <map>

#include "../../AoC/Day/Day.h"

namespace AoC2024 {
    class Day19 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day19() : Day() {
            dayNo = 19;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::string> patterns = {};
        std::vector<std::string> designs = {};

        bool IsValid(const std::string& design, size_t i);
        uint64_t CountValid(std::map<std::string, uint64_t>& memory, const std::string& design, size_t i);
    };
}