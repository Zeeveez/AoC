#include "Day03.h"

#include <algorithm>
#include <numeric>
#include <regex>

namespace AoC2024 {
    namespace Day03 {
        std::vector<std::tuple<std::string, int, int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::tuple<std::string, int, int>> inst = {};

            for (auto& line : input) {
                static const std::regex re("(mul|do|don't)\\((\\d{1,3})?,?(\\d{1,3})?\\)", std::regex::optimize);

                std::string::const_iterator searchStart(line.cbegin());
                std::smatch sm;
                while (std::regex_search(searchStart, line.cend(), sm, re)) {
                    if (sm[1] == "mul" && sm[2].matched && sm[3].matched) {
                        inst.push_back({ sm[1], std::stoi(sm[2]), std::stoi(sm[3]) });
                    }
                    else if (sm[1] != "mul" && !sm[2].matched && !sm[3].matched) {
                        inst.push_back({ sm[1], 0, 0 });
                    }
                    searchStart = sm.suffix().first;
                }
            }

            return inst;
        }

        uint64_t ProcessA(const std::vector<std::string>& input) {
            auto inst = PreProcessInput(input);

            uint64_t res = std::accumulate(
                inst.begin(),
                inst.end(),
                0ui64,
                [](uint64_t acc, const std::tuple<std::string, int, int>& inst) {
                    if (std::get<0>(inst) != "mul") { return acc; }
                    return acc + std::get<1>(inst) * std::get<2>(inst);
                }
            );

            return res;
        }

        uint64_t ProcessB(const std::vector<std::string>& input) {
            auto inst = PreProcessInput(input);

            bool adding = true;
            uint64_t res = std::accumulate(
                inst.begin(),
                inst.end(),
                0ui64,
                [&adding](uint64_t acc, const std::tuple<std::string, int, int>& inst) {
                    if (std::get<0>(inst) == "do") { adding = true; }
                    if (std::get<0>(inst) == "don't") { adding = false; }

                    if (std::get<0>(inst) != "mul" || !adding) { return acc; }

                    return acc + std::get<1>(inst) * std::get<2>(inst);
                }
            );

            return res;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto res = ProcessA(input);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto res = ProcessB(input);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { res, endTime - startTime };
        }
    }
}