#include "Day25.h"

#include <iostream>

namespace AoC2022 {
    namespace Day25 {
        uint64_t SNAFUToInt(std::string snafu) {
            uint64_t val = 0;
            for (auto& c : snafu) {
                val *= 5;
                switch (c) {
                case '0':
                    break;
                case '1':
                    val += 1;
                    break;
                case '2':
                    val += 2;
                    break;
                case '=':
                    val -= 2;
                    break;
                case '-':
                    val -= 1;
                    break;
                }
            }
            return val;
        }

        std::string IntToSNAFU(uint64_t v) {
            std::string snafu = "";
            while (v) {
                int n = v % 5;
                switch (n) {
                case 0:
                    snafu = '0' + snafu;
                    break;
                case 1:
                    snafu = '1' + snafu;
                    break;
                case 2:
                    snafu = '2' + snafu;
                    break;
                case 3:
                    snafu = '=' + snafu;
                    break;
                case 4:
                    snafu = '-' + snafu;
                    break;
                }
                if (n == 3) { v += 2; }
                if (n == 4) { v += 1; }
                v /= 5;
            }
            return snafu;
        }
        std::pair<std::string, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t s = 0;
            for (auto& line : input) {
                s += SNAFUToInt(line);
            }

            auto res = IntToSNAFU(s);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
            auto endtime = std::chrono::high_resolution_clock::now();
            return { "N/A", endtime - starttime };
        }
    }
}