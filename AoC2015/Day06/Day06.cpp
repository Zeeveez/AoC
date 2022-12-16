#include "Day06.h"

#include <regex>

namespace AoC2015 {
    namespace Day06 {

        std::vector<std::tuple<Instruction, int, int, int, int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::tuple<Instruction, int, int, int, int>> instructions = {};

            for (auto& line : input) {
                static const std::regex re("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)", std::regex::optimize);
                std::smatch sm;

                if (std::regex_search(line, sm, re)) {
                    instructions.push_back(
                        {
                            sm[1].str() == "turn on"
                                ? Instruction::ON
                                : sm[1].str() == "turn off"
                                    ? Instruction::OFF
                                    : Instruction::TOGGLE,
                            std::stoi(sm[2]),
                            std::stoi(sm[3]),
                            std::stoi(sm[4]),
                            std::stoi(sm[5])
                        }
                    );
                }
            }

            return instructions;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto instructions = PreProcessInput(input);

            std::vector<std::vector<bool>> grid = {};
            for (int x = 0; x < 1000; x++) {
                grid.push_back({});
                for (int y = 0; y < 1000; y++) {
                    grid[x].push_back(false);
                }
            }

            for (auto& ins : instructions) {
                Instruction state = std::get<0>(ins);
                int x1 = std::get<1>(ins);
                int y1 = std::get<2>(ins);
                int x2 = std::get<3>(ins);
                int y2 = std::get<4>(ins);

                for (int x = x1; x <= x2; x++) {
                    for (int y = y1; y <= y2; y++) {
                        switch (state) {
                        case Instruction::ON:
                            grid[x][y] = true;
                            break;
                        case Instruction::OFF:
                            grid[x][y] = false;
                            break;
                        case Instruction::TOGGLE:
                            grid[x][y] = !grid[x][y];
                            break;
                        }
                    }
                }
            }

            int c = 0;
            for (int x = 0; x < 1000; x++) {
                for (int y = 0; y < 1000; y++) {
                    c += grid[x][y];
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto instructions = PreProcessInput(input);

            std::vector<std::vector<int>> grid = {};
            for (int x = 0; x < 1000; x++) {
                grid.push_back({});
                for (int y = 0; y < 1000; y++) {
                    grid[x].push_back(0);
                }
            }

            for (auto& ins : instructions) {
                Instruction state = std::get<0>(ins);
                int x1 = std::get<1>(ins);
                int y1 = std::get<2>(ins);
                int x2 = std::get<3>(ins);
                int y2 = std::get<4>(ins);

                for (int x = x1; x <= x2; x++) {
                    for (int y = y1; y <= y2; y++) {
                        switch (state) {
                        case Instruction::ON:
                            grid[x][y]++;
                            break;
                        case Instruction::OFF:
                            grid[x][y] = std::max(0, grid[x][y] - 1);
                            break;
                        case Instruction::TOGGLE:
                            grid[x][y] += 2;
                            break;
                        }
                    }
                }
            }

            int c = 0;
            for (int x = 0; x < 1000; x++) {
                for (int y = 0; y < 1000; y++) {
                    c += grid[x][y];
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }
    }
}