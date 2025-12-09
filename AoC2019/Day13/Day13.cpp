#include <map>
#include <numeric>

#include "Day13.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day13::A() {
        IntCodeCPU computer(rawData);
        std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> tiles = {};
        while (!computer.halted) {
            computer.RunToOutput();
            std::int64_t x = computer.Output();
            computer.RunToOutput();
            std::int64_t y = computer.Output();
            computer.RunToOutput();
            std::int64_t tile = computer.Output();
            tiles[std::pair<std::int64_t, std::int64_t>(x, y)] = tile;
        }
        return std::accumulate(tiles.begin(), tiles.end(), 0, [](std::int64_t acc, std::pair<std::pair<std::int64_t, std::int64_t>, std::int64_t> tile) {return acc + (tile.second == 2 ? 1 : 0); });
    }

    AoC::DayResult::PuzzleResult Day13::B() {
        IntCodeCPU computer(rawData);
        computer.memory[0] = 2; // Set F2P
        std::map<std::pair<std::int64_t, std::int64_t>, std::int64_t> tiles = {};
        std::vector<std::int64_t> outputs = { 0,0,0 };
        unsigned int currentOutput = 0;
        std::int64_t paddleX = 15;
        std::int64_t ballX = 15;
        std::int64_t score = 0;
        while (!computer.halted) {
            computer.RunToOutput();
            if (computer.outputReady) {
                outputs[currentOutput++] = computer.Output();
                currentOutput %= 3;
                if (currentOutput == 0) {
                    if (outputs[0] == -1 && outputs[1] == 0) {
                        score = outputs[2];
                    }
                    else {
                        tiles[std::pair<std::int64_t, std::int64_t>(outputs[0], outputs[1])] = outputs[2];
                        if (outputs[2] == 3) { paddleX = outputs[0]; }
                        if (outputs[2] == 4) { ballX = outputs[0]; }
                    }
                }
            }
            computer.Input(paddleX < ballX ? 1 : paddleX > ballX ? -1 : 0);
        }
        return score;
    }
}