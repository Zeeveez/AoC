#include "Day17.h"

#include <regex>
#include <iostream>
#include <numeric>

namespace AoC2024 {
    namespace Day17 {
        std::tuple<std::vector<uint64_t>, std::vector<int>> PreProcessInput(const std::vector<std::string>& input) {
            uint64_t a = std::stoull(input[0].substr(12));
            uint64_t b = std::stoull(input[1].substr(12));
            uint64_t c = std::stoull(input[2].substr(12));

            std::vector<int> prog = {};

            static const std::regex re("(\\d+)", std::regex::optimize);

            std::string::const_iterator searchStart(input[4].cbegin());
            std::smatch sm;
            while (std::regex_search(searchStart, input[4].cend(), sm, re)) {
                prog.push_back(std::stoi(sm[1]));
                searchStart = sm.suffix().first;
            }

            return { { a, b, c }, prog };
        }

        int Tick(std::vector<uint64_t>& regs, std::vector<int>& prog, int& ip) {
            uint64_t operand = prog[ip + 1] < 4 ? prog[ip + 1] : regs[prog[ip + 1] - 4];

            switch (prog[ip]) {
            case 0:
            {
                uint64_t num = regs[0];
                uint64_t den = operand;
                regs[0] = num >> den;
                break;
            }
            case 1:
            {
                uint64_t num = regs[1];
                uint64_t den = prog[ip + 1];
                regs[1] = num ^ den;
                break;
            }
            case 2:
            {
                uint64_t num = operand;
                uint64_t den = 0b111;
                regs[1] = num & den;
                break;
            }
            case 3:
            {
                if (regs[0] == 0) { break; }
                ip = prog[ip + 1] - 2;   // -2 as we add 2 later
                break;
            }
            case 4:
            {
                uint64_t num = regs[1];
                uint64_t den = regs[2];
                regs[1] = num ^ den;
                break;
            }
            case 5:
            {
                ip += 2;
                return operand & 0b111;
            }
            case 6:
            {
                uint64_t num = regs[0];
                uint64_t den = operand;
                regs[1] = num >> den;
                break;
            }
            case 7:
            {
                uint64_t num = regs[0];
                uint64_t den = operand;
                regs[2] = num >> den;
                break;
            }
            }
            ip += 2;
            return -1;
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [regs, prog] = PreProcessInput(input);

            std::string res = "";
            int ip = 0;
            while (ip >= 0 && ip < prog.size()) {
                int output = Tick(regs, prog, ip);
                if (output != -1) {
                    if (res.length()) { res += ","; }
                    res += '0' + output;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<std::vector<uint64_t>, std::vector<uint64_t>> ExtractCycle(std::vector<uint64_t>& maybeCycle) {
            if (maybeCycle.size() < 500) {
                return { {}, {} };
            }
            for (int i = 0; i < maybeCycle.size(); i++) {
                for (int length = 1; length < (maybeCycle.size() - i) / 2; length++) {
                    for (int j = 0; j < length; j++) {
                        if (maybeCycle[i + j] != maybeCycle[i + j + length]) {
                            break;
                        }

                        // Verify
                        for (int x = 0; x + i < maybeCycle.size(); x++) {
                            if (maybeCycle[x + i] != maybeCycle[i + x % length]) {
                                goto bad;
                            }
                        }

                        return {
                            std::vector<uint64_t>(maybeCycle.begin(), maybeCycle.begin() + i),
                            std::vector<uint64_t>(maybeCycle.begin() + i, maybeCycle.begin() + i + length)
                        };

                    bad:;
                    }
                }
            }
            return { {}, {} };
        }

        std::pair<uint64_t, std::vector<uint64_t>> FindCycle(std::vector<uint64_t> state, std::vector<int> prog, int progTarget, uint64_t initA, std::vector<uint64_t>& increments) {
            std::vector<uint64_t> cycle = {};
            int incrementIdx = 0;
            uint64_t startA = initA;
            uint64_t prevStartA = startA;

            while (true) {
                int progProg = 0;
                auto regs = state;
                regs[0] = startA;
                int ip = 0;

                while (ip >= 0 && ip < prog.size()) {
                    int output = Tick(regs, prog, ip);
                    if (output != -1) {
                        if (progProg == progTarget) {
                            if (output != prog[progTarget]) {
                                break;
                            }
                            auto [prelude, cycles] = FindCycle(cycle);
                            if (cycles.size()) {
                                return { initA + std::accumulate(prelude.begin(), prelude.end(), (uint64_t)0), cycles };
                            }
                            else {
                                cycle.push_back(startA - prevStartA);
                                prevStartA = startA;
                                break;
                            }
                        }
                        else {
                            progProg++;
                        }
                    }
                }
                startA += increments[incrementIdx++];
                incrementIdx %= increments.size();
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [origReg, prog] = PreProcessInput(input);
            std::vector<int> newProg;

            uint64_t initValue = 0;
            std::vector<uint64_t> increments = { 1 };
            for (int i = 0; i < prog.size(); i++) {
                auto [start, cycles] = FindCycle(origReg, prog, i, initValue, increments);
                initValue = start;
                increments = cycles;
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { initValue, endtime - starttime };
        }
    }
}