#include "Day07.h"

namespace AoC2024 {
    namespace Day07 {
        bool Valid(const std::vector<uint64_t>& eq, bool withConcat) {
            return Valid(eq[0], eq[1], eq, 2, withConcat);
        }

        bool Valid(uint64_t solution, uint64_t current, const std::vector<uint64_t>& eq, int i, bool withConcat) {
            if (eq.size() == i) {
                return solution == current;
            }
            else {
                if(current > solution){ return false; }
                return Valid(solution, current + eq[i], eq, i + 1, withConcat)
                    || Valid(solution, current * eq[i], eq, i + 1, withConcat)
                    || (withConcat && Valid(solution, Concat(current, eq[i]), eq, i + 1, withConcat));
            }
        }

        uint64_t Concat(uint64_t x, uint64_t y) {
            uint64_t pow = 10;
            while (y >= pow){ pow *= 10; }
            return x * pow + y;
        }

        uint64_t Run(const std::vector<std::string>& input, bool withConcat) {
            uint64_t res = 0;

            for (auto& line : input) {
                std::vector<uint64_t> eq = {};
                auto s = std::stringstream(line);
                std::string tk;
                while (s >> tk) {
                    eq.push_back(std::stoull(tk));
                }
                if (Valid(eq, withConcat)) {
                    res += eq[0];
                }
            }

            return res;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(input);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t res = Run(input, true);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - startTime };
        }
    }
}