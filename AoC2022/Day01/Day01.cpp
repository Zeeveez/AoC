#include "Day01.h"

#include <algorithm>

namespace AoC2022 {
    namespace Day01 {
        std::vector<uint64_t> ProcessAndSort(const std::vector<std::string>& input) {
            std::vector<uint64_t> values = {};
            int c = 0;
            for (auto& line : input) {
                if (line.length() == 0) {
                    values.push_back(c);
                    c = 0;
                }
                else {
                    c += std::stoi(line);
                }
            }

            std::sort(values.begin(), values.end());
            return values;            
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto values = ProcessAndSort(input);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { values[values.size() - 1], endtime - starttime};
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto values = ProcessAndSort(input);
            auto r = values[values.size() - 1] + values[values.size() - 2] + values[values.size() - 3];

            auto endTime = std::chrono::high_resolution_clock::now();
            return { r, endTime - startTime };
        }
    }
}