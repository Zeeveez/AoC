#include <sstream>

#include "Day19.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day19::Load() {
        input = AoC::Helpers::ReadLines("./Day19.txt");
    }

    void Day19::Parse() {
        std::stringstream ss(input[0]);
        std::string towel;
        while (std::getline(ss, towel, ',')) {
            patterns.push_back(Trim(towel));
        }

        designs = std::vector<std::string>(input.begin() + 2, input.end());
    }

    void Day19::A() {
        uint64_t res = 0;
        for (auto& design : designs) {
            if (IsValid(design)) {
                res++;
            }
        }

        partAResult.first = res;
    }

    void Day19::B() {
        std::map<std::string, uint64_t> memory = {};
        uint64_t res = 0;
        for (auto& design : designs) {
            res += CountValid(memory, design);
        }

        partBResult.first = res;
    }

    std::string Day19::Trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) { return str; }
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    bool Day19::IsValid(const std::string& design) {
        for (auto& pattern : patterns) {
            if (design.length() < pattern.length()) { continue; }
            if (design == pattern) {
                return true;
            }

            if (design.substr(0, pattern.length()) == pattern) {
                if (IsValid(design.substr(pattern.length()))) {
                    return true;
                }
            }
        }
        return false;
    }

    uint64_t Day19::CountValid(std::map<std::string, uint64_t>& memory, const std::string& design) {
        uint64_t solutions = 0;
        if (memory.contains(design)) { return memory[design]; }
        for (auto& pattern : patterns) {
            if (design.length() < pattern.length()) { continue; }
            if (design == pattern) {
                solutions += 1;
            }

            if (design.substr(0, pattern.length()) == pattern) {
                solutions += CountValid(memory, design.substr(pattern.length()));
            }
        }
        memory[design] = solutions;
        return solutions;
    }
}