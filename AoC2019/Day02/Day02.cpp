#include "Day02.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day02::A() {
        return RunProgram(rawData, 12, 2);
    }

    AoC::DayResult::PuzzleResult Day02::B() {
        for (std::int64_t noun = 0; noun < 100; noun++) {
            for (std::int64_t verb = 0; verb < 100; verb++) {
                if (RunProgram(rawData, noun, verb) == 19690720) {
                    return 100 * noun + verb;
                }
            }
        }
        return -1;
    }

    std::int64_t Day02::RunProgram(std::vector<std::int64_t> program, std::int64_t noun, std::int64_t verb) {
        IntCodeCPU computer(program);
        computer.memory[1] = noun;
        computer.memory[2] = verb;
        computer.RunToEnd();
        return computer.memory[0];
    }
}