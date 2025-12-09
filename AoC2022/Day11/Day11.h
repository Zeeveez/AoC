#ifndef DAY11_H
#define DAY11_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <queue>
#include <functional>

namespace AoC2022 {
    namespace Day11 {
        class Monkey {
        public:
            std::queue<uint64_t> items;
            uint64_t testVal;
            std::function<uint64_t(uint64_t)> op;
            std::function<bool(uint64_t)> test;
            std::function<void(std::vector<Monkey>&, uint64_t, bool)> throwItem;

            void ParseItems(const std::string& line);
            void ParseOperation(const std::string& line);
            int ParseCondition(const std::string& line);
            int ParseConditionMonkey(const std::string& line);
            void ParseTest(const std::string& line);
            void ParseThrow(const std::vector<std::string>& input, int i);

            Monkey(const std::vector<std::string>& input, int i);
        };
        std::vector<Monkey> ParseMonkeys(const std::vector<std::string> input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif