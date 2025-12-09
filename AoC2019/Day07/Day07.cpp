#include <algorithm>

#include "Day07.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day07::A() {
        std::vector<std::int64_t> permutations = { 0,1,2,3,4 };
        std::int64_t thrust = 0;
        do {
            std::vector<IntCodeCPU> cpus = {};
            for (int i = 0; i < 5; i++) {
                cpus.push_back(IntCodeCPU(rawData));
                cpus[i].Input(permutations[i]);
                cpus[i].RunToInput();
                cpus[i].Input(i == 0 ? 0 : cpus[i - 1].Output());
                cpus[i].RunToOutput();
            }
            thrust = std::max(thrust, cpus[4].Output());
        } while (std::next_permutation(permutations.begin(), permutations.end()));
        return thrust;
    }

    AoC::DayResult::PuzzleResult Day07::B() {
        std::vector<std::int64_t> permutations = { 5,6,7,8,9 };
        std::int64_t thrust = 0;
        do {
            std::vector<IntCodeCPU> cpus = {};
            for (int i = 0; i < 5; i++) {
                cpus.push_back(IntCodeCPU(rawData));
                cpus[i].Input(permutations[i]);
            }
            std::int64_t comp1input = 0;
            while (!cpus[4].halted) {
                for (int i = 0; i < 5; i++) {
                    cpus[i].RunToInput();
                    cpus[i].Input(i == 0 ? comp1input : cpus[i - 1].Output());
                    cpus[i].RunToOutput();
                }
                comp1input = cpus[4].Output();
            }
            thrust = std::max(thrust, comp1input);
        } while (std::next_permutation(permutations.begin(), permutations.end()));
        return thrust;
    }
}