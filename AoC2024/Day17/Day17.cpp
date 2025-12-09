#include <regex>
#include <numeric>

#include "Day17.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day17::Parse() {
        registers = {
            std::stoull(rawData[0].substr(12)),
            std::stoull(rawData[1].substr(12)),
            std::stoull(rawData[2].substr(12))
        };

        const std::regex re("(\\d+)", std::regex::optimize);

        std::string::const_iterator searchStart(rawData[4].cbegin());
        std::smatch sm;
        while (std::regex_search(searchStart, rawData[4].cend(), sm, re)) {
            program.push_back(std::stoi(sm[1]));
            searchStart = sm.suffix().first;
        }
    }

    AoC::DayResult::PuzzleResult Day17::A() {
        std::string res = "";
        auto registers = this->registers;
        int ip = 0;
        while (ip >= 0 && ip < program.size()) {
            int output = Tick(registers, ip);
            if (output != -1) {
                if (res.length()) { res += ","; }
                res += '0' + output;
            }
        }
        this->registers = registers;

        return res;
    }

    AoC::DayResult::PuzzleResult Day17::B() {
        std::vector<int> newProg;

        uint64_t initValue = 0;
        std::vector<uint64_t> increments = { 1 };
        for (int i = 0; i < program.size(); i++) {
            auto [prelude, cycles] = FindCycle(registers, i, initValue, increments);
            initValue += std::accumulate(prelude.begin(), prelude.end(), (uint64_t)0);
            increments = cycles;
        }

        return initValue;
    }

    int Day17::Tick(std::vector<uint64_t>& regs, int& ip) {
        uint64_t operand = program[ip + 1] < 4 ? program[ip + 1] : regs[program[ip + 1] - 4];

        switch (program[ip]) {
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
            uint64_t den = program[ip + 1];
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
            ip = program[ip + 1] - 2;   // -2 as we add 2 later
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

    std::pair<std::vector<uint64_t>, std::vector<uint64_t>> Day17::ExtractCycle(std::vector<uint64_t>& maybeCycle) {
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

    std::pair<std::vector<uint64_t>, std::vector<uint64_t>> Day17::FindCycle(std::vector<uint64_t> state, int progTarget, uint64_t initA, std::vector<uint64_t>& increments) {
        std::vector<uint64_t> cycle = {};
        int incrementIdx = 0;
        uint64_t startA = initA;
        uint64_t prevStartA = startA;

        while (true) {
            int progProg = 0;
            auto regs = state;
            regs[0] = startA;
            int ip = 0;

            while (ip >= 0 && ip < program.size()) {
                int output = Tick(regs, ip);
                if (output != -1) {
                    if (progProg == progTarget) {
                        if (output != program[progTarget]) {
                            break;
                        }
                        auto [prelude, cycles] = ExtractCycle(cycle);
                        if (cycles.size()) {
                            return { prelude, cycles };
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
}