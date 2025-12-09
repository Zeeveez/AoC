#include "Day04.h"

#include <regex>

namespace AoC2022 {
    namespace Day04 {
        std::pair<std::pair<int, int>, std::pair<int, int>> PreProcessLine(const std::string& line) {
#ifdef NDEBUG
            int i = 0;
            int f0 = 0;
            while (line[i] != '-') { f0 = f0 * 10 + line[i] - '0'; i++; } i++;
            int t0 = 0;
            while (line[i] != ',') { t0 = t0 * 10 + line[i] - '0'; i++; } i++;
            int f1 = 0;
            while (line[i] != '-') { f1 = f1 * 10 + line[i] - '0'; i++; } i++;
            int t1 = 0;
            while (i != line.length()) { t1 = t1 * 10 + line[i] - '0'; i++; }

            return { { f0, t0 }, { f1, t1 } };
#else
            static const std::regex re("(\\d+)\\-(\\d+),(\\d+)\\-(\\d+)", std::regex::optimize);
            std::smatch sm;

            if (std::regex_search(line, sm, re)) {
                return {
                    {
                        std::stoi(sm[1]),
                        std::stoi(sm[2])
                    },
                    {
                        std::stoi(sm[3]),
                        std::stoi(sm[4])
                    }
                };
            }
#endif
        }

        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PreProcessLines(const std::vector<std::string>& lines) {
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> data = {};
            for (auto& line : lines) {
                data.push_back(PreProcessLine(line));
            }
            return data;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
            auto data = PreProcessLines(input);

            int result = 0;

            for (auto& cleaningCrew : data) {
                auto elf1 = cleaningCrew.first;
                auto elf2 = cleaningCrew.second;
                if ((elf1.first >= elf2.first && elf1.second <= elf2.second)
                    || (elf2.first >= elf1.first && elf2.second <= elf1.second)) {
                    result++;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { result, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto data = PreProcessLines(input);

            int result = 0;

            for (auto& cleaningCrew : data) {
                auto elf1 = cleaningCrew.first;
                auto elf2 = cleaningCrew.second;
                if (std::max(elf1.first, elf2.first) <= std::min(elf1.second, elf2.second)) {
                    result++;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { result, endtime - startTime };
        }
    }
}