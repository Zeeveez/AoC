#include <numeric>
#include <cstdint>

#include "Day03.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day03::Parse() {
        for (auto& line : rawData) {
            for (std::size_t i = 0; i < line.size(); i++) {
                if (line[i] == 'm' && i < line.size() - 3 && line[i + 1] == 'u' && line[i + 2] == 'l' && line[i + 3] == '(') {
                    i += 4;
                    int v1 = 0;
                    for (std::size_t j = 0; j < 3; j++) {
                        if (line[i] >= '0' && line[i] <= '9') {
                            v1 = v1 * 10 + line[i] - '0';
                            i++;
                        }
                        else {
                            break;
                        }
                    }
                    if (v1 == 0 || line[i] != ',') { continue; }
                    i++;
                    int v2 = 0;
                    for (size_t j = 0; j < 3; j++) {
                        if (line[i] >= '0' && line[i] <= '9') {
                            v2 = v2 * 10 + line[i] - '0';
                            i++;
                        }
                        else {
                            break;
                        }
                    }
                    if (v2 == 0 || line[i] != ')') { continue; }
                    instructions.push_back({ Instruction::MUL, v1, v2 });
                }
                else if (i < line.size() - 3 && line[i] == 'd' && line[i + 1] == 'o') {
                    if (line[i + 2] == '(' && line[i + 3] == ')') {
                        instructions.push_back({ Instruction::DO, 0, 0 });
                        i += 3;
                    }
                    else if (i < line.size() - 6 && line[i + 2] == 'n' && line[i + 3] == '\'' && line[i + 4] == 't' && line[i + 5] == '(' && line[i + 6] == ')') {
                        instructions.push_back({ Instruction::DONT, 0, 0 });
                        i += 6;
                    }
                }
            }
        }
    }

    AoC::DayResult::PuzzleResult Day03::A() {
        uint64_t res = std::accumulate(
            instructions.begin(),
            instructions.end(),
            (std::uint64_t)0,
            [](std::uint64_t acc, const std::tuple<Instruction, int, int>& inst) {
                return acc + (std::get<0>(inst) == Instruction::MUL ? std::get<1>(inst) * std::get<2>(inst) : 0);
            }
        );

        return res;
    }

    AoC::DayResult::PuzzleResult Day03::B() {
        bool adding = true;
        return std::accumulate(
            instructions.begin(),
            instructions.end(),
            (std::uint64_t)0,
            [&adding](std::uint64_t acc, const std::tuple<Instruction, int, int>& inst) {
                if (std::get<0>(inst) == Instruction::DO) { adding = true; return acc; }
                else if (std::get<0>(inst) == Instruction::DONT) { adding = false; return acc; }
                // MUL
                return acc + (adding ? std::get<1>(inst) * std::get<2>(inst) : 0);
            }
        );
    }
}