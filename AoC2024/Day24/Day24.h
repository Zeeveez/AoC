#pragma once
#include "../../AoC/Day/Day.h"

#include <vector>
#include <string>
#include <map>

namespace AoC2024 {
    class Day24 : public AoC::Day {
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
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day24() : Day() {
            dayNo = 24;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::map<std::string, int> wires = {};
        std::vector<std::pair<Gate, bool>> gates = {};
    };
}