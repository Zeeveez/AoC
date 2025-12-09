#pragma once
#include "../../Shared/Day/Day.h"

#include <vector>
#include <string>
#include <map>

namespace AoC2024 {
    class Day24 : public AoC::Day<std::vector<std::string>, 2024, 24> {
    private:
        struct Gate {
            enum class Operator {
                AND,
                OR,
                XOR
            };
            Operator type = Operator::AND;
            std::string wire1 = "";
            std::string wire2 = "";
            std::string wire3 = "";

            Gate() = default;
            Gate(std::string def);
            bool Process(std::map<std::string, int>& wires);
        };

    public:
        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

    private:
        std::map<std::string, int> wires = {};
        std::vector<std::pair<Gate, bool>> gates = {};
    };
}