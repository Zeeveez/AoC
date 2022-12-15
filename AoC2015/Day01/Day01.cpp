#include "Day01.h"

namespace AoC2015 {
    namespace Day01 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int64_t n = 0;
            for (auto& c : input) {
                n += c == '(' ? 1 : -1;
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { n, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            int64_t n = 0;
            uint64_t r = 0;
            for (auto& c : input) {
                r++;
                n += c == '(' ? 1 : -1;
                if (n < 0) { break; }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { r, endTime - startTime };
        }
    }
}