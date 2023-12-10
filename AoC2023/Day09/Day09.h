#ifndef DAY09_H
#define DAY09_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>

namespace AoC2023 {
    namespace Day09 {
        std::vector<int64_t> ParseLine(const std::string& input);
        int64_t ProcessA(const std::vector<int64_t>& data);
        int64_t ProcessB(const std::vector<int64_t>& data);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif