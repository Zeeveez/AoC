#include <cstdint>

#include "Day16.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day16::A() {
        auto input = rawData;
        for (int i = 0; i < 100; i++) {
            input = ProcessString(input);
        }
        return input.substr(0, 8);
    }

    AoC::DayResult::PuzzleResult Day16::B() {
        std::string signal = "0000007-1";
        //for (int i = 0; i < 10000; i++) {
        //    signal += input;
        //}
        //for (int i = 0; i < 100; i++) {
        //    signal = ProcessString(signal);
        //}
        return "NYI";// signal.substr(std::atoi(signal.substr(0, 7).c_str()), 8);
    }

    int Day16::GetPatternNumber(long long i, long long n) {
        switch (((i + 1) / (n + 1)) % 4) {
        case 1: return 1;
        case 3: return -1;
        default: return 0;
        }
    }

    std::string Day16::ProcessString(std::string input) {
        std::string output = "";
        for (int i = 0; i < input.length(); i++) {
            long long op = 0;
            for (int j = i; j < input.length(); j++) {
                int patNum = GetPatternNumber(j, i);
                if (patNum == 0) {
                    j += i;
                    continue;
                }
                op += patNum * (input[j] - '0');
            }
            output += (std::abs(op) % 10 + '0');
        }
        return output;
    }
}