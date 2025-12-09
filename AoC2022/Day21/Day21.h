#ifndef DAY21_H
#define DAY21_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>

namespace AoC2022 {
    namespace Day21 {
        class Monkey {
        public:
            bool hasValue;
            int64_t value;
            int monkey1;
            int monkey2;
            char op;

            Monkey();
            Monkey(int64_t value);
            Monkey(int monkey1, int monkey2, char op);

            int64_t Score(std::unordered_map<int, Monkey>& monkeys);
            bool IsTargetInTree(std::unordered_map<int, Monkey>& monkeys, int target);
            bool IsTargetOnLeft(std::unordered_map<int, Monkey>& monkeys, int target);
        };

        int StringifyMonkey(std::string input, int i);

        std::unordered_map<int, Monkey> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif