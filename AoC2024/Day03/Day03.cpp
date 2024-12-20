#include <regex>
#include <numeric>

#include "Day03.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day03::Load() {
        input = AoC::Helpers::ReadLines("./Day03.txt");
    }

    void Day03::Parse() {
        static const std::regex re("(mul|do|don't)\\((\\d{1,3})?,?(\\d{1,3})?\\)", std::regex::optimize);

        instructions = {};

        for (auto& line : input) {
            std::string::const_iterator searchStart(line.cbegin());
            std::smatch sm;
            while (std::regex_search(searchStart, line.cend(), sm, re)) {
                if (sm[1] == "mul" && sm[2].matched && sm[3].matched) {
                    instructions.push_back({ sm[1], std::stoi(sm[2]), std::stoi(sm[3]) });
                }
                else if (sm[1] != "mul" && !sm[2].matched && !sm[3].matched) {
                    instructions.push_back({ sm[1], 0, 0 });
                }
                searchStart = sm.suffix().first;
            }
        }
    }

    void Day03::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = std::accumulate(
            instructions.begin(),
            instructions.end(),
            0ui64,
            [](uint64_t acc, const std::tuple<std::string, int, int>& inst) {
                if (std::get<0>(inst) != "mul") { return acc; }
                return acc + std::get<1>(inst) * std::get<2>(inst);
            }
        );

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day03::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        bool adding = true;
        uint64_t res = std::accumulate(
            instructions.begin(),
            instructions.end(),
            0ui64,
            [&adding](uint64_t acc, const std::tuple<std::string, int, int>& inst) {
                if (std::get<0>(inst) == "do") { adding = true; }
                if (std::get<0>(inst) == "don't") { adding = false; }

                if (std::get<0>(inst) != "mul" || !adding) { return acc; }

                return acc + std::get<1>(inst) * std::get<2>(inst);
            }
        );

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }
}