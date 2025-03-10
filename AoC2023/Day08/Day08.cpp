#include <numeric>

#include "Day08.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day08::Load() {
        input = AoC::Helpers::ReadLines("./Day08.txt");
    }

    void Day08::Parse() {
        instructions = input[0];
        for (size_t i = 2; i < input.size(); i++) {
            int from = (input[i][0] - 'A') * 26 * 26 + (input[i][1] - 'A') * 26 + (input[i][2] - 'A');
            int toL = (input[i][7] - 'A') * 26 * 26 + (input[i][8] - 'A') * 26 + (input[i][9] - 'A');
            int toR = (input[i][12] - 'A') * 26 * 26 + (input[i][13] - 'A') * 26 + (input[i][14] - 'A');
            paths[from] = { toL, toR };
        }
    }

    void Day08::A() {
        size_t res = 0;
        size_t pos = 0;         // AAA = 0
        while (pos != 17575) {  // ZZZ = 17575
            pos = instructions[res++ % instructions.length()] == 'L' ? paths.at(pos).first : paths.at(pos).second;
        }
        partAResult.first = res;
    }

    void Day08::B() {
        uint64_t res = 1;
        for (auto& [start, _] : paths) {
            if (start % 26 != 0) { continue; }
            size_t pos = start;
            size_t distance = 0;
            while (pos % 26 != 25) {
                pos = instructions[distance++ % instructions.length()] == 'L' ? paths.at(pos).first : paths.at(pos).second;
            }
            res = std::lcm(res, distance);
        }
        partBResult.first = res;
    }
}