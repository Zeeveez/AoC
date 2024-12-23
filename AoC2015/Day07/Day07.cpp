#include <regex>

#include <iostream>

#include "Day07.h"

#include "../../Helpers/Helpers.h"

namespace AoC2015 {
    Day07::Part::Part(std::string def) {
        auto substrs = AoC::Helpers::SplitString(def, ' ');

        id = GetId(substrs.back());

        int input1Idx = -1;
        int input2Idx = -1;
        int operandIdx = -1;

        if (substrs.size() == 3) {
            // Immediate value
            input1Idx = 0;
        }
        else if (substrs.size() == 4) {
            // NOT
            input1Idx = 1;
            operandIdx = 0;
        }
        else {
            // Binary Op
            input1Idx = 0;
            input2Idx = 2;
            operandIdx = 1;
        }

        if (input1Idx != -1) {
            if (substrs[input1Idx][0] >= '0' && substrs[input1Idx][0] <= '9') {
                // Immediate
                input1 = (std::uint16_t)std::stoi(substrs[input1Idx]);
            }
            else {
                inputPart1Id = GetId(substrs[input1Idx]);
            }
        }

        if (input2Idx != -1) {
            if (substrs[input2Idx][0] >= '0' && substrs[input2Idx][0] <= '9') {
                // Immediate
                input2 = (std::uint16_t)std::stoi(substrs[input2Idx]);
            }
            else {
                inputPart2Id = GetId(substrs[input2Idx]);
            }
        }

        if (operandIdx != -1) {
            switch (substrs[operandIdx][0]) {
            case 'A':
                type = Operator::AND;
                break;
            case 'O':
                type = Operator::OR;
                break;
            case 'L':
                type = Operator::LSHIFT;
                break;
            case 'R':
                type = Operator::RSHIFT;
                break;
            case 'N':
                type = Operator::NOT;
                break;
            }
        }
    }

    std::size_t Day07::Part::GetId(std::string label) {
        size_t id = 0;
        for (auto& c : label) {
            id = id * 26 + c - 'a';
        }
        return id;
    }

    void Day07::Part::AssignInputs(const std::unordered_map<int, Part>& parts) {
        if (inputPart1Id != -1) {
            input1 = &parts.at(inputPart1Id);
        }
        if (inputPart2Id != -1) {
            input2 = &parts.at(inputPart2Id);
        }
    }

    std::uint16_t Day07::Part::GetOutput() const {
        auto v1 = inputPart1Id != -1 ? std::get<const Part*>(input1)->GetOutput() : std::get<std::uint16_t>(input1);
        auto v2 = inputPart2Id != -1 ? std::get<const Part*>(input2)->GetOutput() : std::get<std::uint16_t>(input2);

        switch (type) {
        case Operator::AND:
            return v1 & v2;
            break;
        case Operator::OR:
            return v1 | v2;
            break;
        case Operator::LSHIFT:
            return v1 << v2;
            break;
        case Operator::RSHIFT:
            return v1 >> v2;
            break;
        case Operator::NOT:
            return ~v1;
            break;
        case Operator::NONE:
            return v1;
            break;
        };
        throw;
    }

    void Day07::Load() {
        input = AoC::Helpers::ReadLines("./Day07.txt");
    }

    void Day07::Parse() {
        for (auto& line : input) {
            Part p = Part(line);
            parts[p.id] = p;
        }
        for (auto& [id, part] : parts) {
            part.AssignInputs(parts);
        }
    }

    void Day07::A() {
        uint64_t res = parts[Part::GetId("a")].GetOutput();
        partAResult.first = res;
    }

    void Day07::B() {
        partBResult.first = "";
    }
}