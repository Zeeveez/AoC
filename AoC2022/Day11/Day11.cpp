#include "Day11.h"

#include <regex>

namespace AoC2022 {
    namespace Day11 {
        Monkey::Monkey(const std::vector<std::string>& input, int i) {
            ParseItems(input[i + 1]);
            ParseOperation(input[i + 2]);
            ParseTest(input[i + 3]);
            ParseThrow(input, i);
        }

        void Monkey::ParseItems(const std::string& line) {
            items = {};
            std::string::const_iterator searchStart(line.cbegin());
            const std::regex re("(\\d+)");
            std::smatch sm;
            while (std::regex_search(searchStart, line.cend(), sm, re)) {
                items.push(std::stoi(sm[1]));
                searchStart = sm.suffix().first;
            }
        }

        void Monkey::ParseOperation(const std::string& line) {
            const std::regex re("([\\+\\*]) (\\d+|old)");
            std::smatch sm;
            std::regex_search(line, sm, re);
            char op = sm[1].str()[0];
            if (sm[2].str() == "old") {
                if (op == '+') {
                    this->op = [](uint64_t old) {
                        return old + old;
                    };
                }
                else {
                    this->op = [](uint64_t old) {
                        return old * old;
                    };
                }
            }
            else {
                int val = std::stoi(sm[2]);
                if (op == '+') {
                    this->op = [val](uint64_t old) {
                        return old + val;
                    };
                }
                else {
                    this->op = [val](uint64_t old) {
                        return old * val;
                    };
                }
            }
        }

        int Monkey::ParseCondition(const std::string& line) {
            const std::regex re("(\\d+)");
            std::smatch sm;
            std::regex_search(line, sm, re);
            return std::stoi(sm[1]);
        }

        int Monkey::ParseConditionMonkey(const std::string& line) {
            const std::regex re("(\\d+)");
            std::smatch sm;
            std::regex_search(line, sm, re);
            return std::stoi(sm[1]);
        }

        void Monkey::ParseTest(const std::string& line) {
            uint64_t testVal = ParseCondition(line);
            this->testVal = testVal;

            test = [=](uint64_t val) {
                return val % testVal == 0;
            };
        }

        void Monkey::ParseThrow(const std::vector<std::string>& input, int i) {
            int trueMonkey = ParseConditionMonkey(input[i + 4]);
            int falseMonkey = ParseConditionMonkey(input[i + 5]);

            throwItem = [=](std::vector<Monkey>& monkeys, uint64_t val, bool throwCondition) {
                monkeys[throwCondition ? trueMonkey : falseMonkey].items.push(val);
            };
        }

        std::vector<Monkey> ParseMonkeys(const std::vector<std::string> input) {
            std::vector<Monkey> monkeys = {};

            for (int i = 0; i < input.size(); i += 7) {
                monkeys.push_back(Monkey(input, i));
            }
            return monkeys;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto monkeys = ParseMonkeys(input);
            std::vector<uint64_t> monkeyInspections = {};
            for (int i = 0; i < monkeys.size(); i++) { monkeyInspections.push_back(0); }

            for (int rounds = 0; rounds < 20; rounds++) {
                for (int i = 0; i < monkeys.size(); i++) {
                    monkeyInspections[i] += monkeys[i].items.size();
                    while (monkeys[i].items.size()) {

                        auto worry = monkeys[i].items.front();
                        monkeys[i].items.pop();
                        worry = monkeys[i].op(worry);
                        worry /= 3;
                        bool throwCondition = monkeys[i].test(worry);
                        monkeys[i].throwItem(monkeys, worry, throwCondition);

                    }
                }
            }

            std::sort(monkeyInspections.begin(), monkeyInspections.end());
            uint64_t res = monkeyInspections[monkeyInspections.size() - 1] * monkeyInspections[monkeyInspections.size() - 2];

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto monkeys = ParseMonkeys(input);
            std::vector<uint64_t> monkeyInspections = {};
            uint64_t safeMod = 1;
            for (int i = 0; i < monkeys.size(); i++) {
                monkeyInspections.push_back(0);
                safeMod *= monkeys[i].testVal;
            }

            for (int rounds = 0; rounds < 10000; rounds++) {
                for (int i = 0; i < monkeys.size(); i++) {
                    monkeyInspections[i] += monkeys[i].items.size();
                    while (monkeys[i].items.size()) {

                        auto worry = monkeys[i].items.front(); monkeys[i].items.pop();
                        worry = monkeys[i].op(worry);
                        bool throwCondition = monkeys[i].test(worry);
                        worry %= safeMod;
                        monkeys[i].throwItem(monkeys, worry, throwCondition);

                    }
                }
            }

            std::sort(monkeyInspections.begin(), monkeyInspections.end());
            uint64_t res = monkeyInspections[monkeyInspections.size() - 1] * monkeyInspections[monkeyInspections.size() - 2];

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}