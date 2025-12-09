#include "Day05.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day05::A() {
        return RunProgram(rawData, 1);
    }

    AoC::DayResult::PuzzleResult Day05::B() {
        return RunProgram(rawData, 5);
    }

    std::int64_t Day05::RunProgram(std::vector<std::int64_t> program, std::int64_t systemID) {
        IntCodeCPU computer(program);
        computer.Input(systemID);
        computer.RunToEnd();
        return computer.Output();
    }
}