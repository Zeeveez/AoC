#include "Day09.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day09::A() {
        IntCodeCPU computer(rawData);
        computer.Input(1);
        computer.RunToEnd();
        return computer.Output();
    }

    AoC::DayResult::PuzzleResult Day09::B() {
        IntCodeCPU computer(rawData);
        computer.Input(2);
        computer.RunToEnd();
        return computer.Output();
    }
}