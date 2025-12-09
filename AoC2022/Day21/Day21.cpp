#include "Day21.h"

#include <iostream>

namespace AoC2022 {
    namespace Day21 {
        Monkey::Monkey() {
            hasValue = true;
            this->value = 0;
        }
        Monkey::Monkey(int64_t value) {
            hasValue = true;
            this->value = value;
        }
        Monkey::Monkey(int monkey1, int monkey2, char op) {
            hasValue = false;
            this->monkey1 = monkey1;
            this->monkey2 = monkey2;
            this->op = op;
        }

        int StringifyMonkey(std::string input, int i) {
            return (input[i] - 'a') * 26 * 26 * 26
                + (input[i + 1] - 'a') * 26 * 26
                + (input[i + 2] - 'a') * 26
                + (input[i + 3] - 'a');
        }

        int64_t Monkey::Score(std::unordered_map<int, Monkey>& monkeys) {
            if (!hasValue) {
                switch (op) {
                case '+':
                    value = monkeys[monkey1].Score(monkeys) + monkeys[monkey2].Score(monkeys);
                    break;
                case '-':
                    value = monkeys[monkey1].Score(monkeys) - monkeys[monkey2].Score(monkeys);
                    break;
                case '*':
                    value = monkeys[monkey1].Score(monkeys) * monkeys[monkey2].Score(monkeys);
                    break;
                case '/':
                    value = monkeys[monkey1].Score(monkeys) / monkeys[monkey2].Score(monkeys);
                    break;
                case '=':
                    value = monkeys[monkey1].Score(monkeys) == monkeys[monkey2].Score(monkeys);
                    break;
                }
                hasValue = true;
            }
            return value;
        }

        bool Monkey::IsTargetInTree(std::unordered_map<int, Monkey>& monkeys, int target) {
            if (hasValue == true) {
                return false;
            }
            if (monkey1 == target) {
                return true;
            }
            if (monkey2 == target) {
                return true;
            }
            return monkeys[monkey1].IsTargetInTree(monkeys, target) || monkeys[monkey2].IsTargetInTree(monkeys, target);
        }

        bool Monkey::IsTargetOnLeft(std::unordered_map<int, Monkey>& monkeys, int target) {
            return monkey1 == target || monkeys[monkey1].IsTargetInTree(monkeys, target);
        }

        std::unordered_map<int, Monkey> PreProcessInput(const std::vector<std::string>& input) {
            std::unordered_map<int, Monkey> monkeys = {};
            for (auto& line : input) {
                int monkey = StringifyMonkey(line, 0);
                if (std::isdigit(line[6])) {
                    int64_t value = std::stoi(line.substr(6));
                    monkeys[monkey] = Monkey(value);
                }
                else {
                    int monkey1 = StringifyMonkey(line, 6);
                    char op = line[11];
                    int monkey2 = StringifyMonkey(line, 13);
                    monkeys[monkey] = Monkey(monkey1, monkey2, op);
                }
            }
            return monkeys;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto monkeys = PreProcessInput(input);
            int64_t res = monkeys[StringifyMonkey("root", 0)].Score(monkeys);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int64_t targetVal = 0;
            auto monkeys = PreProcessInput(input);
            int me = StringifyMonkey("humn", 0);
            int at = StringifyMonkey("root", 0);
            monkeys[at].op = '=';

            while (true) {
                if (at == me) {
                    break;
                }
                if (monkeys[at].IsTargetOnLeft(monkeys, me)) {
                    switch (monkeys[at].op) {
                    case '+':
                        targetVal = targetVal - monkeys[monkeys[at].monkey2].Score(monkeys);
                        break;
                    case '-':
                        targetVal = targetVal + monkeys[monkeys[at].monkey2].Score(monkeys);
                        break;
                    case '*':
                        targetVal = targetVal / monkeys[monkeys[at].monkey2].Score(monkeys);
                        break;
                    case '/':
                        targetVal = targetVal * monkeys[monkeys[at].monkey2].Score(monkeys);
                        break;
                    case '=':
                        targetVal = monkeys[monkeys[at].monkey2].Score(monkeys);
                        break;
                    }
                    at = monkeys[at].monkey1;
                }
                else {
                    switch (monkeys[at].op) {
                    case '+':
                        targetVal = targetVal - monkeys[monkeys[at].monkey1].Score(monkeys);
                        break;
                    case '-':
                        targetVal = monkeys[monkeys[at].monkey1].Score(monkeys) - targetVal;
                        break;
                    case '*':
                        targetVal = targetVal / monkeys[monkeys[at].monkey1].Score(monkeys);
                        break;
                    case '/':
                        targetVal = monkeys[monkeys[at].monkey1].Score(monkeys) / targetVal;
                        break;
                    case '=':
                        targetVal = monkeys[monkeys[at].monkey1].Score(monkeys);
                        break;
                    }
                    at = monkeys[at].monkey2;
                }
            }



            auto endtime = std::chrono::high_resolution_clock::now();
            return { targetVal, endtime - starttime };
        }
    }
}