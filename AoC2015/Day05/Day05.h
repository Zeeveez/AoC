#ifndef DAY05_H
#define DAY05_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day05 {
        inline bool VowelTest(const std::string& s);
        inline bool DoubleTest(const std::string& s);
        inline bool BadPairTest(const std::string& s);
        inline bool DoublePairTest(const std::string& s);
        inline bool DoubleGapTest(const std::string& s);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif