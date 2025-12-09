#include "Day16.h"

#include <regex>
#include <queue>
#include <set>

namespace AoC2022 {
    namespace Day16 {
        std::pair<std::vector<int>, std::unordered_map<int, std::vector<int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<int> flowRates = { };
            flowRates.resize(input.size());
            std::unordered_map<int, int> valveMappings = { { 0, 0 } };
            std::unordered_map<int, std::vector<int>> corridors = {};

            for (auto& line : input) {
                std::string::const_iterator searchStart(line.cbegin());
                const std::regex valveRe("([A-Z][A-Z])");
                const std::regex flowRe("(\\d+)");
                std::smatch sm;

                std::regex_search(line, sm, flowRe);
                int flowRate = std::stoi(sm[1]);

                int firstValve = -1;
                while (std::regex_search(searchStart, line.cend(), sm, valveRe)) {
                    int valve = (sm[1].str()[0] - 'A') * 26 + (sm[1].str()[1] - 'A');
                    if (!valveMappings.contains(valve)) {
                        valveMappings[valve] = valveMappings.size();
                    }

                    int valveIdx = valveMappings[valve];

                    if (firstValve == -1) {
                        firstValve = valveIdx;
                        corridors[valveIdx] = {};
                        flowRates[valveIdx] = flowRate;
                    }
                    else {
                        corridors[firstValve].push_back(valveIdx);
                    }
                    searchStart = sm.suffix().first;
                }
            }

            return { flowRates, corridors };
        }

        int GetDistance(const std::unordered_map<int, std::vector<int>>& corridors, int from, int to) {
            std::set<int> visited = { from };
            std::queue<std::pair<int, int>> queue = {};
            for (auto& corridor : corridors.at(from)) {
                queue.push({ corridor, 1 });
            }
            int distance = 0;
            while (!queue.empty()) {
                auto [at, cost] = queue.front(); queue.pop();
                if (at == to) {
                    return cost;
                }
                visited.insert(at);
                for (auto& corridor : corridors.at(at)) {
                    if (!visited.contains(corridor)) {
                        queue.push({ corridor, cost + 1 });
                    }
                }
            }
        }

        std::vector<std::unordered_map<int, int>> GetValveRoutes(const std::vector<int>& flowRates, const std::unordered_map<int, std::vector<int>>& corridors) {
            std::vector<std::unordered_map<int, int>> weightedCorridors = {};
            weightedCorridors.resize(flowRates.size());
            for (int from = 0; from < flowRates.size(); from++) {
                if (from == 0 || flowRates[from] != 0) {
                    for (int to = 0; to < flowRates.size(); to++) {
                        if (from != to && flowRates[to] != 0) {
                            weightedCorridors[from][to] = GetDistance(corridors, from, to);
                        }
                    }
                }
            }
            return weightedCorridors;
        }

        int RunSimulations(const std::vector<int>& flowRates, const std::vector<std::unordered_map<int, int>>& corridors, uint64_t visited, int location, int timeLeft) {
            if (timeLeft <= 1) { return 0; }
            if (location && (visited & ((uint64_t)1 << location))) { return 0; }

            int score = (timeLeft - 1) * flowRates.at(location);

            int maxPath = 0;
            for (auto& corridor : corridors.at(location)) {
                auto& [dest, cost] = corridor;
                maxPath = std::max(maxPath, RunSimulations(flowRates, corridors, visited | ((uint64_t)1 << location), dest, timeLeft - cost - 1));
            }

            return score + maxPath;
        }

        void RunSimulationsAsPair(const std::vector<int>& flowRates, const std::vector<std::unordered_map<int, int>>& corridors, std::unordered_map<uint64_t, int>& visitedScores, uint64_t visited, int location, int timeLeft, int runningScore, int& maxScore) {
            if (timeLeft <= 0) { return; }
            if (visited & ((uint64_t)1 << location)) { return; }
            uint64_t newVisited = visited | ((uint64_t)1 << location);

            runningScore += (timeLeft - 1) * flowRates.at(location);
            if (!visitedScores.contains(newVisited)) {
                // Increased time by 1 to account for method which opens valve AA (which has 0 flowrate)
                visitedScores[newVisited] = RunSimulations(flowRates, corridors, newVisited, 0, 26 + 1);
            }
            maxScore = std::max(maxScore, runningScore + visitedScores[newVisited]);

            for (auto& corridor : corridors.at(location)) {
                int dest = corridor.first;
                int cost = corridor.second;
                RunSimulationsAsPair(flowRates, corridors, visitedScores, newVisited, dest, timeLeft - cost - 1, runningScore, maxScore);
            }
        }

        int RunSimulationsAsPair(const std::vector<int>& flowRates, const std::vector<std::unordered_map<int, int>>& corridors, int location, int timeLeft) {
            std::unordered_map<uint64_t, int> visitedScores = {};
            uint64_t visited = 0;
            int maxScore = 0;
            RunSimulationsAsPair(flowRates, corridors, visitedScores, visited, location, timeLeft + 1, 0, maxScore);
            return maxScore;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [flowRates, corridors] = PreProcessInput(input);
            auto weightedCorridors = GetValveRoutes(flowRates, corridors);

            // Increased time by 1 to account for method which opens valve AA (which has 0 flowrate)
            int res = RunSimulations(flowRates, weightedCorridors, 0, 0, 30 + 1);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [flowRates, corridors] = PreProcessInput(input);
            auto weightedCorridors = GetValveRoutes(flowRates, corridors);

            // Increased time by 1 to account for method which opens valve AA (which has 0 flowrate)
            int res = RunSimulationsAsPair(flowRates, weightedCorridors, 0, 26);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}