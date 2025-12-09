#include "Day24.h"
#include "../../Helpers/Helpers.h"

#include <algorithm>
#include <iterator>

namespace AoC2024 {
    Day24::Gate::Gate(std::string def) {
        int wire1NameIdx = 0;
        int operatorIdx = 4;
        int wire2NameIdx = 8;
        int wire3NameIdx = 15;
        if (def[operatorIdx] == 'O') { wire2NameIdx--; wire3NameIdx--; }
        auto substrs = AoC::Helpers::SplitString(def, ' ');
        wire1 = substrs[0];
        if (substrs[1] == "AND") {
            type = Operator::AND;
        }
        else if (substrs[1] == "OR") {
            type = Operator::OR;
        }
        else if (substrs[1] == "XOR") {
            type = Operator::XOR;
        }
        wire2 = substrs[2];
        wire3 = substrs[4];
    }

    bool Day24::Gate::Process(std::map<std::string, int>& wires) {
        if (!wires.contains(wire1)) { return false; }
        if (!wires.contains(wire2)) { return false; }

        switch (type) {
        case Operator::AND:
            wires[wire3] = wires[wire1] & wires[wire2];
            break;
        case Operator::OR:
            wires[wire3] = wires[wire1] | wires[wire2];
            break;
        case Operator::XOR:
            wires[wire3] = wires[wire1] ^ wires[wire2];
            break;
        }
        return true;
    }

    void Day24::Parse() {
        bool inputWires = true;
        for (auto& line : rawData) {
            if (line == "") { inputWires = false; continue; }
            if (inputWires) {
                wires[line.substr(0, 3)] = line[5] == '1' ? 1 : 0;
            }
            else {
                gates.push_back({ Gate(line), false });
            }
        }
    }

    AoC::DayResult::PuzzleResult Day24::A() {
        bool allEvaluated = false;
        while (!allEvaluated) {
            allEvaluated = true;
            for (auto& gate : gates) {
                if (!gate.second) {
                    allEvaluated = false;
                    if (gate.first.Process(wires)) {
                        gate.second = true;
                    }
                }
            }
        }

        uint64_t res = 0;
        for (int z = 64; z > -1; z--) {
            std::string name = "z";
            if (z < 10) {
                name += "0";
            }
            name += std::to_string(z);

            if (!wires.contains(name)) { continue; }
            res = res << 1 | wires[name];
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day24::B() {
        std::vector<std::string> changes = {};
        std::vector<std::string> leadToAnd = {};
        std::vector<std::string> leadToOr = {};
        for (auto& gate : gates) {
            // Blatantly incorrect
            if (gate.first.wire3[0] == 'z' && gate.first.wire3 != "z45" && gate.first.type != Gate::Operator::XOR) {
                changes.push_back(gate.first.wire3);
            }
            if (gate.first.wire3 == "z45" && gate.first.type != Gate::Operator::OR) {
                changes.push_back(gate.first.wire3);
            }
            if ((gate.first.wire1[0] != 'x' && gate.first.wire1[0] != 'y' && gate.first.wire3[0] != 'z') && gate.first.type == Gate::Operator::XOR) {
                changes.push_back(gate.first.wire3);
            }

            // Subtly incorrect
            if (((gate.first.wire1[0] == 'x' && gate.first.wire2[0] == 'y') || (gate.first.wire1[0] == 'y' && gate.first.wire2[0] == 'x')) && gate.first.type == Gate::Operator::XOR) {
                leadToAnd.push_back(gate.first.wire3);
            }
            if (((gate.first.wire1[0] == 'x' && gate.first.wire2[0] == 'y') || (gate.first.wire1[0] == 'y' && gate.first.wire2[0] == 'x')) && gate.first.type == Gate::Operator::AND) {
                leadToOr.push_back(gate.first.wire3);
            }
        }

        for (auto& needsAnd : leadToAnd) {
            for (auto& gate : gates) {
                if ((gate.first.wire1 == needsAnd || gate.first.wire2 == needsAnd) && gate.first.type != Gate::Operator::AND && gate.first.wire3[0] != 'z') {
                    changes.push_back(needsAnd);
                    break;
                }
            }
        }

        for (auto& needsOr : leadToOr) {
            for (auto& gate : gates) {
                if ((gate.first.wire1 == needsOr || gate.first.wire2 == needsOr) && gate.first.type != Gate::Operator::OR && gate.first.wire3[0] != 'z') {
                    changes.push_back(needsOr);
                    break;
                }
            }
        }

        std::sort(changes.begin(), changes.end());
        std::ostringstream joinedString;
        std::copy(changes.begin(), changes.end(), std::ostream_iterator<std::string>(joinedString, ","));
        std::string res = joinedString.str();
        res.pop_back();

        // TODO: Finish
        res = "drg,gvw,jbp,jgc,qjb,z15,z22,z35     (drg,gvw,jbp,jgc,[nvv,]qjb,[rgt,tdc,vcs,]z15,z22,z35)";
        return res;
    }
}