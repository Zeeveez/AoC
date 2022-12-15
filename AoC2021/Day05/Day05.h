#ifndef DAY05_H
#define DAY05_H

#include <vector>
#include <string>
#include <map>
#include <chrono>

namespace AoC2021 {
    namespace Day05 {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PreProcessInput(const std::vector<std::string>& input);

        void DrawPoint(std::map<std::pair<int, int>, int>& vents, const std::pair<int, int> p);
        void DrawLine(std::map<std::pair<int, int>, int>& vents, const std::pair<int, int>& p1, const std::pair<int, int>& p2, bool drawDiagonals);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input, bool drawDiagonals = false);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif