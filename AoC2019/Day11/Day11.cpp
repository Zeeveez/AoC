#include <map>
#include <algorithm>

#include "Day11.h"
#include "../IntCodeCPU/IntCodeCPU.h"
#include "../../Helpers/Helpers.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day11::A() {
        IntCodeCPU computer(rawData);
        std::map<std::pair<int, int>, long long> panels = {};
        int x = 0;
        int y = 0;
        int dir = 0; // Up
        while (!computer.halted) {
            computer.Input(panels.count(std::pair<int, int>(x, y)) == 0 ? 0 : panels[std::pair<int, int>(x, y)]);
            computer.RunToOutput();
            panels[std::pair<int, int>(x, y)] = computer.Output();
            computer.RunToOutput();
            dir += computer.Output() == 0 ? -1 : 1;
            dir = dir < 0 ? dir + 4 : dir;
            switch (dir % 4) {
            case 0:
                y += 1;
                break;
            case 1:
                x += 1;
                break;
            case 2:
                y -= 1;
                break;
            case 3:
                x -= 1;
                break;
            }
        }
        return panels.size();
    }

    AoC::DayResult::PuzzleResult Day11::B() {
        IntCodeCPU computer(rawData);
        std::map<std::pair<int, int>, long long> panels = { { std::pair<int, int>(0, 0), 1 } };
        int x = 0;
        int y = 0;
        int dir = 0; // Up
        while (!computer.halted) {
            computer.Input(panels.count(std::pair<int, int>(x, y)) == 0 ? 0 : panels[std::pair<int, int>(x, y)]);
            computer.RunToOutput();
            panels[std::pair<int, int>(x, y)] = computer.Output();
            computer.RunToOutput();
            dir += computer.Output() == 0 ? -1 : 1;
            dir = dir < 0 ? dir + 4 : dir;
            switch (dir % 4) {
            case 0:
                y += 1;
                break;
            case 1:
                x += 1;
                break;
            case 2:
                y -= 1;
                break;
            case 3:
                x -= 1;
                break;
            }
        }
        int xMin = (*std::min_element(panels.begin(), panels.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int xMax = (*std::max_element(panels.begin(), panels.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.first < panel2.first.first;
                                      })).first.first;
        int yMin = (*std::min_element(panels.begin(), panels.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;
        int yMax = (*std::max_element(panels.begin(), panels.end(),
                                      [](const auto& panel1, const auto& panel2) {
                                          return panel1.first.second < panel2.first.second;
                                      })).first.second;

        std::string output = "";
        for (int y = yMax; y > yMin - 1; y--) {
            for (int x = xMin + 1; x < xMax - 1; x++) {
                output += panels[std::pair<int, int>(x, y)] == 0 ? ' ' : '#';
            }
        }
        return AoC::Helpers::ParseDrawnString(output, 8);
    }
}