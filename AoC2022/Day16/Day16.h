#ifndef DAY16_H
#define DAY16_H

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day16 {
        std::pair<std::vector<int>, std::unordered_map<int, std::vector<int>>> PreProcessInput(const std::vector<std::string>& input);

        int GetDistance(const std::unordered_map<int, std::vector<int>>& corridors, int from, int to);
        std::vector<std::unordered_map<int, int>> GetValveRoutes(const std::vector<int>& flowRates, const std::unordered_map<int, std::vector<int>>& corridors);

        int RunSimulations(const std::vector<int>& flowRates, const std::vector<std::unordered_map<int, int>>& corridors, uint64_t visited, int location, int timeLeft);

        void RunSimulationsAsPair(const std::vector<int>& flowRates, const std::vector<std::unordered_map<int, int>>& corridors, std::unordered_map<uint64_t, int>& visitedScores, uint64_t visited, int location, int timeLeft, int runningScore, int& maxScore);
        int RunSimulationsAsPair(const std::vector<int>& flowRates, const std::vector<std::unordered_map<int, int>>& corridors, int location, int timeLeft);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif