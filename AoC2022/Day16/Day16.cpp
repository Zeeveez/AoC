#include "Day16.h"

#include <regex>
#include <queue>

#include <iostream>

namespace AoC2022 {
    namespace Day16 {
        std::pair<std::unordered_map<int, int>, std::unordered_map<int, std::vector<int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::unordered_map<int, int> flowRates = {};
            std::unordered_map<int, std::vector<int>> corridors = {};

            for (auto& line : input) {
                std::string::const_iterator searchStart(line.cbegin());
                const std::regex valveRe("([A-Z][A-Z])");
                const std::regex flowRe("(\\d+)");
                std::smatch sm;

                int flowRate = 0;
                std::regex_search(line, sm, flowRe);
                flowRate = std::stoi(sm[1]);

                int firstValve = -1;
                while (std::regex_search(searchStart, line.cend(), sm, valveRe)) {
                    int valve = (sm[1].str()[0] - 'A') * 26 + (sm[1].str()[1] - 'A');
                    if (firstValve == -1) {
                        firstValve = valve;
                        flowRates[firstValve] = flowRate;
                        corridors[firstValve] = {};
                    }
                    else {
                        corridors[firstValve].push_back(valve);
                    }
                    searchStart = sm.suffix().first;
                }
            }

            return { flowRates, corridors };
        }

        std::unordered_map<int, int> GetUsefulFlowRates(const std::unordered_map<int, int>& flowRates) {
            std::unordered_map<int, int> usefulFlowRates = {};
            for (auto& flowRate : flowRates) {
                if (flowRate.second != 0 || flowRate.first == 0) {
                    usefulFlowRates.insert(flowRate);
                }
            }
            return usefulFlowRates;
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

        std::unordered_map<int, std::unordered_map<int, int>> GetValveRoutes(const std::unordered_map<int, int>& usefulFlowRates, const std::unordered_map<int, std::vector<int>>& corridors) {
            std::unordered_map<int, std::unordered_map<int, int>> weightedCorridors = {};
            for (auto& from : usefulFlowRates) {
                weightedCorridors[from.first] = {};
                for (auto& to : usefulFlowRates) {
                    if (from != to) {
                        weightedCorridors[from.first][to.first] = GetDistance(corridors, from.first, to.first);
                    }
                }
            }
            return weightedCorridors;
        }

        int RunSimulations(const std::unordered_map<int, int>& flowRates, const std::unordered_map<int, std::unordered_map<int, int>>& corridors, std::set<int>& visited, int location, int timeLeft) {
            if (timeLeft <= 0) {
                return 0;
            }

            int score = (timeLeft - 1) * flowRates.at(location);

            int maxPath = 0;
            for (auto& corridor : corridors.at(location)) {
                auto& [dest, cost] = corridor;

                if (!visited.contains(dest)) {
                    visited.insert(dest);
                    maxPath = std::max(maxPath, RunSimulations(flowRates, corridors, visited, dest, timeLeft - cost - (location == 0 ? 0 : 1)));
                    visited.erase(dest);
                }
            }

            return score + maxPath;
        }

        int RunSimulations(const std::unordered_map<int, int>& flowRates, const std::unordered_map<int, std::unordered_map<int, int>>& corridors, int location, int timeLeft) {
            std::set<int> visited = { location };
            return RunSimulations(flowRates, corridors, visited, location, timeLeft);
            visited.erase(location);
        }

        void RunSimulationsAsPair(const std::unordered_map<int, int>& flowRates, const std::unordered_map<int, std::unordered_map<int, int>>& corridors, std::set<int>& visited, int location1, int location2, int timeLeft1, int timeLeft2, int runningScore, int& maxScore) {
            if (timeLeft1 <= 0) {
                return;
            }
            runningScore += (timeLeft1 - 1) * flowRates.at(location1);
            maxScore = std::max(maxScore, runningScore + RunSimulations(flowRates, corridors, visited, location2, timeLeft2));

            for (auto& corridor : corridors.at(location1)) {
                int dest = corridor.first;
                if (!visited.contains(corridor.first)) {
                    visited.insert(corridor.first);
                    int cost = corridor.second;
                    RunSimulationsAsPair(flowRates, corridors, visited, dest, location2, timeLeft1 - cost - (location1 == 0 ? 0 : 1), timeLeft2, runningScore, maxScore);

                    visited.erase(corridor.first);
                }
            }
        }

        int RunSimulationsAsPair(const std::unordered_map<int, int>& flowRates, const std::unordered_map<int, std::unordered_map<int, int>>& corridors, int location1, int location2, int timeLeft1, int timeLeft2) {
            std::set<int> visited = { location1 };
            int maxScore = 0;
            RunSimulationsAsPair(flowRates, corridors, visited, location1, location2, timeLeft1, timeLeft2, 0, maxScore);
            return maxScore;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [flowRates, corridors] = PreProcessInput(input);
            auto usefulFlowRates = GetUsefulFlowRates(flowRates);
            auto weightedCorridors = GetValveRoutes(usefulFlowRates, corridors);

            int res = RunSimulations(usefulFlowRates, weightedCorridors, 0, 30);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [flowRates, corridors] = PreProcessInput(input);
            auto usefulFlowRates = GetUsefulFlowRates(flowRates);
            auto weightedCorridors = GetValveRoutes(usefulFlowRates, corridors);

            int res = RunSimulationsAsPair(usefulFlowRates, weightedCorridors, 0, 0, 26, 26);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}