#ifndef DAY02_H
#define DAY02_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day02 {
        std::tuple<uint64_t, uint64_t, uint64_t> ReadBox(std::string str);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif