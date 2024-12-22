#include "Day13.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day13::Load() {
        input = AoC::Helpers::ReadLines("./Day13.txt");
    }

    void Day13::Parse() {
        for (int i = 0; i < input.size(); i += 4) {
            std::pair<uint64_t, uint64_t> acase = { (input[i][12] - '0') * 10 + (input[i][13] - '0'), (input[i][18] - '0') * 10 + (input[i][19] - '0') };
            std::pair<uint64_t, uint64_t> bcase = { (input[i + 1][12] - '0') * 10 + (input[i + 1][13] - '0'), (input[i + 1][18] - '0') * 10 + (input[i + 1][19] - '0') };

            int j = 9;
            uint64_t tx = 0;
            uint64_t ty = 0;
            while (input[i + 2][j] != ',') {
                tx = tx * 10 + input[i + 2][j++] - '0';
            }
            while (input[i + 2][j++] != '=') {}
            while (j < input[i + 2].length()) {
                ty = ty * 10 + input[i + 2][j++] - '0';
            }
            testCases.push_back({ acase, bcase, { tx, ty } });
        }
    }

    void Day13::A() {
        uint64_t res = 0;
        for (auto& testCase : testCases) {
            res += Solve(testCase);
        }

        partAResult.first = res;
    }

    void Day13::B() {
        uint64_t res = 0;
        for (auto& testCase : testCases) {
            std::get<2>(testCase).first += 10000000000000;
            std::get<2>(testCase).second += 10000000000000;
            res += Solve(testCase);
        }

        partBResult.first = res;
    }

    uint64_t Day13::Solve(const std::tuple<std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>, std::pair<uint64_t, uint64_t>>& testCase) {
        int64_t ax = std::get<0>(testCase).first;
        int64_t ay = std::get<0>(testCase).second;
        int64_t bx = std::get<1>(testCase).first;
        int64_t by = std::get<1>(testCase).second;
        int64_t tx = std::get<2>(testCase).first;
        int64_t ty = std::get<2>(testCase).second;

        int64_t bs = bx * ay - by * ax;
        int64_t ts = tx * ay - ty * ax;

        if (ts % bs != 0) { return 0; }
        int64_t b = ts / bs;
        int64_t a = (tx - b * bx) / ax;
        if (a * ax + b * bx != tx) { return 0; }

        return a * 3 + b;
    }
}