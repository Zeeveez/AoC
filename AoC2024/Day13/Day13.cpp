#include "Day13.h"

#include <algorithm>
#include <numeric>
#include <regex>
#include <iostream>

namespace AoC2024 {
    namespace Day13 {
        std::vector<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>> cases = {};

            static const std::regex are("Button A: X([\\+\\-]\\d+), Y([\\+\\-]\\d+)", std::regex::optimize);
            static const std::regex bre("Button B: X([\\+\\-]\\d+), Y([\\+\\-]\\d+)", std::regex::optimize);
            static const std::regex pre("Prize: X=(\\d+), Y=(\\d+)", std::regex::optimize);
            for (int i = 0; i < input.size(); i += 4) {
                std::smatch sm;
                std::pair<uint64_t, uint64_t> acase;
                std::string::const_iterator asearchStart(input[i].cbegin());
                if (std::regex_search(asearchStart, input[i].cend(), sm, are)) {
                    acase = { std::stoi(sm[1]), std::stoi(sm[2]) };
                }
                std::pair<uint64_t, uint64_t> bcase;
                std::string::const_iterator bsearchStart(input[i + 1].cbegin());
                if (std::regex_search(bsearchStart, input[i + 1].cend(), sm, bre)) {
                    bcase = { std::stoi(sm[1]), std::stoi(sm[2]) };
                }

                std::pair<uint64_t, uint64_t> pcase;
                std::string::const_iterator psearchStart(input[i + 2].cbegin());
                if (std::regex_search(psearchStart, input[i + 2].cend(), sm, pre)) {
                    pcase = { std::stoi(sm[1]), std::stoi(sm[2]) };
                }
                cases.push_back({ acase, bcase, pcase });
            }
            return cases;
        }

        uint64_t Solve(const std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>& testCase) {
            uint64_t ax = std::get<0>(testCase).first;
            uint64_t ay = std::get<0>(testCase).second;
            uint64_t bx = std::get<1>(testCase).first;
            uint64_t by = std::get<1>(testCase).second;
            uint64_t tx = std::get<2>(testCase).first;
            uint64_t ty = std::get<2>(testCase).second;

            std::tuple<uint64_t, uint64_t, uint64_t> eq1 = { ax * ay, bx * ay, tx * ay };   // Multiply all by ax
            std::tuple<uint64_t, uint64_t, uint64_t> eq2 = { ay * ax, by * ax, ty * ax };   // Multiply all by ay

            std::pair<uint64_t, uint64_t> eqb;

            // Take positive eq cause unsigned types
            if (tx * ay > ty * ax) {
                eqb = { bx * ay - by * ax, tx * ay - ty * ax };
            }
            else {
                eqb = { by * ax - bx * ay, ty * ax - tx * ay };
            }
            
            // if non-0 remainder, invalid solution
            if (eqb.second % eqb.first != 0) {
                return 0;
            }
            uint64_t b = eqb.second / eqb.first;
            uint64_t a = (tx - b * bx) / ax;
            if (a * ax + b * bx != tx) {
                return 0;
            }

            return a * 3 + b;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
            uint64_t res = 0;

            auto cases = PreProcessInput(input);
            for (auto& testCase : cases) {
                res += Solve(testCase);
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            uint64_t res = 0;

            auto cases = PreProcessInput(input);
            for (auto& testCase : cases) {
                std::get<2>(testCase).first += 10000000000000;
                std::get<2>(testCase).second += 10000000000000;
                res += Solve(testCase);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { res, endTime - startTime };
        }
    }
}