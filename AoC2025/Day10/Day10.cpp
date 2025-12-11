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

    int Day10::Machine::CountRequiredLightButtons() {
        int best = std::numeric_limits<int>::max();
        CountRequiredLightButtons(0, best);
        return best;
    }

    void Day10::Machine::CountRequiredLightButtons(std::uint64_t currentLights, int& best, int runningTotal, int index) {
        if (runningTotal >= best) { return; }
        if (currentLights == requiredLights) { best = runningTotal; return; }
        if (index >= buttonValues.size()) { return; }

        CountRequiredLightButtons(currentLights, best, runningTotal, index + 1);
        CountRequiredLightButtons(currentLights ^ buttonValues[index], best, runningTotal + 1, index + 1);
    }

    int Day10::Machine::CountRequiredVoltageButtons() {
        int presses = 0;
        for (int kkk = 0; kkk < 5; kkk++) {
            /*
    button0 button1 button2 button3 button4 button5 button6 button7 button8 button9|     clicks
    1       0       0       0       0       0       0       0       0       1      |     148        => button0 clicks + button9 clicks  = 148
    0       1       0       0       0       0       0       0       0       0      |     1          => button1 click                    = 1
    0       0       1       0       0       0       0       0       0       -1     |     7          => button2 clicks - button9 clicks  = 7     (i.e. however many times you click button 9, click button 2 an additional 7 times)
    0       0       0       1       0       0       0       0       0       0      |     5          => button3 clicks                   = 5
    0       0       0       0       1       0       0       0       0       1      |     8          => button4 clicks + button9 clicks  = 8
    0       0       0       0       0       1       0       0       0       1      |     15         => button5 clicks + button9 clicks  = 15
    0       0       0       0       0       0       1       0       0       0      |     17         => button6 clicks                   = 17
    0       0       0       0       0       0       0       1       0       0      |     14         => button7 clicks                   = 14
    0       0       0       0       0       0       0       0       1       1      |     20         => button8 clicks + button9 clicks  = 20
            */
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
            Gauss::System system = Gauss::System(equations);
            //if(kkk == 0) {std::cout << system << "\n\n";}
            if (system.Solve()) {
                for (auto& equation : system.equations) {
                    presses += equation.result;
                }
                return presses;
            }
            else {
                //std::cout << system << "\n\n";
                for (auto& equation : system.equations) {
                    if (equation.IsSolved()) {
                        for (int i = 0; i < equation.coefficients.size(); i++) {
                            if (equation.coefficients[i] == 1) {
                                presses += equation.result;
                                for (auto& voltageIdx : buttonMappings[i]) {
                                    voltages[voltageIdx] -= equation.result;
                                }
                                buttonMappings[i] = {};
                                break;
                            }
                        }
                    }
                    else {
                        int one = -1;
                        int minusone = -1;
                        bool bad = false;
                        for (int i = 0; i < equation.coefficients.size(); i++) {
                            if (equation.coefficients[i] == 1) {
                                if (one != -1) { bad = true; break; }
                                one = i;
                            }
                            else if (equation.coefficients[i] == -1) {
                                if (minusone != -1) { bad = true; break; }
                                minusone = i;
                            }
                            else if (equation.coefficients[i] != 0) { bad = true; break; }
                        }

                        if (!bad) {
                            if (equation.result > 0) {
                                // offset between presses, press the higher button by required offset
                                presses += equation.result;
                                for (auto& voltageIdx : buttonMappings[one]) {
                                    voltages[voltageIdx] -= equation.result;
                                }
                            }
                        }
                    }
                }
            }
        }
        int best = std::numeric_limits<int>::max();
        CountRequiredVoltageButtons(voltages, best, 0, 0);
        return presses + best;
    }

    void Day10::Machine::CountRequiredVoltageButtons(std::vector<int>& currentVoltages, int& best, int runningTotal, int index) {
        if (runningTotal >= best) { return; }
        if (index >= buttonMappings.size()) { return; }
        bool finished = true;
        for (auto& voltage : currentVoltages) {
            if (voltage < 0) { return; }
            if (voltage != 0) { finished = false; }
        }
        if (finished) { best = runningTotal; return; }

        auto adjust = 1;
        // If index is last in list, offset by remaining amount
        if (index == buttonMappings.size() - 1) {
            for (auto& mapping : buttonMappings[index]) { adjust = std::max(currentVoltages[mapping], adjust); }
        }

        if (buttonMappings[index].size() == 0) {
            CountRequiredVoltageButtons(currentVoltages, best, runningTotal, index + 1);
        }
        else {
            for (auto& mapping : buttonMappings[index]) { currentVoltages[mapping] -= adjust; }
            CountRequiredVoltageButtons(currentVoltages, best, runningTotal + adjust, index);
            for (auto& mapping : buttonMappings[index]) { currentVoltages[mapping] += adjust; }
            CountRequiredVoltageButtons(currentVoltages, best, runningTotal, index + 1);
        }
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
            std::cout << machine.line << " => ";
            auto v = machine.CountRequiredVoltageButtons();
            res += v;
            std::cout << v << "\n";
        }

        return res;
    }
}