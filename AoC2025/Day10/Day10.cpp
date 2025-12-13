#include <stack>
#include <limits>
#include <cmath>
#include <algorithm>

#include "Day10.h"

#include "../../Helpers/GaussianElimination.h"

namespace AoC2025 {
    Day10::Machine::Machine(std::string& line) : line(line) {
        int i = 0;
        ParseLights(line, i);
        ParseButtons(line, i);
        ParseVoltages(line, i);
    }

    void Day10::Machine::ParseLights(std::string& line, int& i) {
        std::stack<int> stack = {};
        while (true) {
            switch (line[i++]) {
            case '.':
                stack.push(0);
                break;
            case '#':
                stack.push(1);
                break;
            case ']':
                requiredLights = 0;
                while (stack.size()) {
                    requiredLights = requiredLights << 1 | stack.top(); stack.pop();
                }
                return;
            }
        }
    }

    void Day10::Machine::ParseButtons(std::string& line, int& i) {
        buttonValues = {};
        buttonMappings = {};
        int buttonLight = 0;
        std::uint64_t buttonValue = 0;
        while (true) {
            auto c = line[i++];
            if (c == '(') { buttonMappings.push_back({}); }
            else if (c == ',') {
                buttonValue |= 1 << buttonLight;
                buttonMappings.back().push_back(buttonLight); buttonLight = 0;
            }
            else if (c == ')') {
                buttonValue |= 1 << buttonLight;
                buttonMappings.back().push_back(buttonLight); buttonLight = 0;
                buttonValues.push_back(buttonValue); buttonValue = 0;
            }
            else if (c >= '0' && c <= '9') {
                buttonLight = buttonLight * 10 + c - '0';
            }
            else if (c == '{') {
                return;
            }
        }
    }

    void Day10::Machine::ParseVoltages(std::string& line, int& i) {
        voltages = {};
        std::uint64_t voltage = 0;
        while (true) {
            auto c = line[i++];
            if (c == ',') {
                voltages.push_back(voltage); voltage = 0;
            }
            else if (c >= '0' && c <= '9') {
                voltage = voltage * 10 + c - '0';
            }
            else if (c == '}') {
                voltages.push_back(voltage);
                break;
            }
        }
    }

    void Day10::Machine::Press(int buttonIdx, int noTimes) {
        for (int i = 0; i < noTimes; i++) {
            for (auto& buttonEffect : buttonMappings[buttonIdx]) {
                voltages[buttonEffect] -= 1;
            }
        }
    }

    int Day10::Machine::CountRequiredLightButtons() {
        int best = std::numeric_limits<int>::max();
        CountRequiredLightButtons(requiredLights, 0, best);
        return best;
    }

    void Day10::Machine::CountRequiredLightButtons(std::uint64_t requiredLights, std::uint64_t currentLights, int& best, int runningTotal, int index) {
        if (runningTotal >= best) { return; }
        if (currentLights == requiredLights) { best = runningTotal; return; }
        if (index >= buttonValues.size()) { return; }

        CountRequiredLightButtons(requiredLights, currentLights, best, runningTotal, index + 1);
        CountRequiredLightButtons(requiredLights, currentLights ^ buttonValues[index], best, runningTotal + 1, index + 1);
    }

    int Day10::Machine::CountRequiredVoltageButtons() {
        int presses = 0;
        std::vector<std::vector<std::int64_t>> equationCoefficients = {};
        for (int i = 0; i < voltages.size(); i++) { equationCoefficients.push_back({}); }
        for (auto& buttonMapping : buttonMappings) {
            for (int i = 0; i < voltages.size(); i++) { equationCoefficients[i].push_back(0); }
            for (auto& voltageIdx : buttonMapping) {
                equationCoefficients[voltageIdx].back()++;
            }
        }
        std::vector<Gauss::Equation> equations = {};
        for (int i = 0; i < equationCoefficients.size(); i++) {
            equations.push_back(Gauss::Equation(equationCoefficients[i], voltages[i]));
        }
        std::vector<int64_t> maximums = {};
        for (int i = 0; i < buttonMappings.size(); i++) {
            int max = std::numeric_limits<int>::max();
            for (auto& mapping : buttonMappings[i]) {
                max = std::min(max, voltages[mapping]);
            }
            maximums.push_back(max);
        }
        Gauss::System system = Gauss::System(equations);
        system.Reduce();
        auto t = system.GetPossibleSolutions(maximums);
        int max = std::numeric_limits<int>::max();
        for (auto& s : t) {
            int locres = 0;
            for (auto& c : s) {
                locres += c;
            }
            max = std::min(max, locres);
        }
        return max;
    }

    void Day10::Parse() {
        machines = {};
        for (auto& line : rawData) {
            if (line == "") { continue; }
            machines.push_back(Machine(line));
        }
    }

    AoC::DayResult::PuzzleResult Day10::A() {
        std::int64_t res = 0;

        for (auto& machine : machines) {
            res += machine.CountRequiredLightButtons();
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day10::B() {
        std::int64_t res = 0;

        for (auto& machine : machines) {
            res += machine.CountRequiredVoltageButtons();
        }

        return res;
    }
}