#include <sstream>
#include <cstring>

#include "Day19.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day19::Parse() {
        std::stringstream ss(rawData[0]);
        std::string towel;
        while (std::getline(ss, towel, ',')) {
            patterns.push_back(AoC::Helpers::Trim(towel));
        }

        designs = std::vector<std::string>(rawData.begin() + 2, rawData.end());
    }

    AoC::DayResult::PuzzleResult Day19::A() {
        uint64_t res = 0;
        for (auto& design : designs) {
            if (IsValid(design, 0)) {
                res++;
            }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day19::B() {
        std::map<std::string, uint64_t> memory = {};
        uint64_t res = 0;
        for (auto& design : designs) {
            res += CountValid(memory, design, 0);
        }

        return res;
    }

    bool Day19::IsValid(const std::string& design, size_t i) {
        for (auto& pattern : patterns) {
            if (pattern.length() + i > design.length()) { continue; }

            if (std::memcmp(design.c_str() + i, pattern.c_str(), pattern.length()) == 0) {
                if (pattern.length() + i == design.length()) {
                    return true;
                }
                else if (IsValid(design, i + pattern.length())) {
                    return true;
                }
            }
        }
        return false;
    }

    uint64_t Day19::CountValid(std::map<std::string, uint64_t>& memory, const std::string& design, size_t i) {
        uint64_t solutions = 0;
        std::string cd = design.substr(i);
        if (memory.contains(cd)) { return memory[cd]; }

        for (auto& pattern : patterns) {
            if (pattern.length() + i > design.length()) { continue; }

            if (std::memcmp(design.c_str() + i, pattern.c_str(), pattern.length()) == 0) {
                if (pattern.length() + i == design.length()) {
                    solutions += 1;
                }
                else {
                    solutions += CountValid(memory, design, i + pattern.length());
                }
            }
        }
        memory[cd] = solutions;
        return solutions;
    }
}