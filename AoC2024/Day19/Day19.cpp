#include "Day19.h"

#include <sstream>

namespace AoC2024 {
    namespace Day19 {
        std::string Trim(const std::string& str) {
            size_t first = str.find_first_not_of(' ');
            if (std::string::npos == first)
            {
                return str;
            }
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }

        std::pair<std::vector<std::string>, std::vector<std::string>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::string> patterns = {};

            std::stringstream ss(input[0]);
            std::string towel;
            while (std::getline(ss, towel, ',')) {
                patterns.push_back(Trim(towel));
            }

            auto designs = std::vector<std::string>(input.begin() + 2, input.end());

            return { patterns, designs };
        }

        bool IsValid(const std::vector<std::string>& patterns, const std::string design) {
            for (auto& pattern : patterns) {
                if (design.length() < pattern.length()) { continue; }
                if (design == pattern) {
                    return true;
                }

                if (design.substr(0, pattern.length()) == pattern) {
                    if (IsValid(patterns, design.substr(pattern.length()))) {
                        return true;
                    }
                }
            }
            return false;
        }

        uint64_t CountValid(const std::vector<std::string>& patterns, std::map<std::string, uint64_t>& memory, const std::string design) {
            uint64_t solutions = 0;
            if (memory.contains(design)) { return memory[design]; }
            for (auto& pattern : patterns) {
                if (design.length() < pattern.length()) { continue; }
                if (design == pattern) {
                    solutions += 1;
                }

                if (design.substr(0, pattern.length()) == pattern) {
                    solutions += CountValid(patterns, memory, design.substr(pattern.length()));
                }
            }
            memory[design] = solutions;
            return solutions;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [patterns, designs] = PreProcessInput(input);
            uint64_t res = 0;
            for (auto& design : designs) {
                if (IsValid(patterns, design)) {
                    res++;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [patterns, designs] = PreProcessInput(input);

            std::map<std::string, uint64_t> memory = {};
            uint64_t res = 0;
            for (auto& design : designs) {
                res += CountValid(patterns, memory, design);
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}