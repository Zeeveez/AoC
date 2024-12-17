#ifndef DAY17_H
#define DAY17_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day17 {
        std::tuple<std::vector<uint64_t>, std::vector<int>> PreProcessInput(const std::vector<std::string>& input);
        
        std::pair<std::string, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);

        std::pair<std::vector<uint64_t>, std::vector<uint64_t>> ExtractCycle(std::vector<uint64_t>& maybeCycle);
        std::pair<uint64_t, std::vector<uint64_t>> FindCycle(std::vector<uint64_t> state, std::vector<int> prog, int progTarget, uint64_t initA, std::vector<uint64_t>& increments);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif