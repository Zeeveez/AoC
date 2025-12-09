#ifndef DAY15_H
#define DAY15_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day15 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input);
        std::vector<std::vector<int>> ConvertToFullMap(const std::vector<std::vector<int>>& input);
        
        std::vector<std::vector<int>> FindCosts(const std::vector<std::vector<int>>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif