#include "Day21.h"

#include <algorithm>
#include <map>
#include <tuple>

namespace AoC2021 {
    namespace Day21 {
        std::pair<int, int> PreProcessInput(const std::vector<std::string>& input) {
            return { input[4][0] - '0', input[9][0] - '0' };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto positions = PreProcessInput(input);
            std::pair<int, int> scores = { 0, 0 };
            int roll = 1;
            uint64_t rolls = 0;

            while (true) {
                for (int i = 0; i < 3; i++) { positions.first += roll++; rolls++; }
                while (positions.first > 10) { positions.first -= 10; }
                scores.first += positions.first;
                if (scores.first >= 1000) { break; }

                for (int i = 0; i < 3; i++) { positions.second += roll++; rolls++; }
                while (positions.second > 10) { positions.second -= 10; }
                scores.second += positions.second;
                if (scores.second >= 1000) { break; }
            }

            uint64_t result = std::min(scores.first, scores.second) * rolls;

            auto endTime = std::chrono::high_resolution_clock::now();
            return { result, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto positions = PreProcessInput(input);
            const std::vector<std::pair<int, int>> rolls = { { 3, 1 }, { 4, 3 }, { 5, 6 }, { 6, 7 }, { 7, 6 }, { 8, 3 }, { 9, 1 } };

            std::pair<uint64_t, uint64_t> scores = { 0, 0 };

            std::map<std::tuple<int, int, int, int, int>, uint64_t> gameStates = {};
            gameStates[{ positions.first, positions.second, 0, 0, 1 }] = 1;

            while (gameStates.size()) {
                auto currentState = gameStates.begin()->first;
                int p1Pos = std::get<0>(currentState);
                int p2Pos = std::get<1>(currentState);
                int p1Score = std::get<2>(currentState);
                int p2Score = std::get<3>(currentState);
                int playerTurn = std::get<4>(currentState);
                int nextPlayer = playerTurn == 1 ? 2 : 1;
                uint64_t gameCount = gameStates[currentState];
                gameStates.erase(currentState);

                if (playerTurn == 1) {
                    for (auto& [outcome, outcomeCount] : rolls) {
                        int newP1Pos = p1Pos + outcome;
                        while (newP1Pos > 10) { newP1Pos -= 10; }
                        int newP1Score = p1Score + newP1Pos;
                        if (newP1Score >= 21) {
                            scores.first += gameCount * outcomeCount;
                        }
                        else {
                            std::tuple<int, int, int, int, int> newState = { newP1Pos, p2Pos, newP1Score, p2Score, nextPlayer };
                            if (gameStates.contains(newState)) {
                                gameStates[newState] += gameCount * outcomeCount;
                            }
                            else {
                                gameStates[newState] = gameCount * outcomeCount;
                            }
                        }
                    }
                }
                else {
                    for (auto& [outcome, outcomeCount] : rolls) {
                        int newP2Pos = p2Pos + outcome;
                        while (newP2Pos > 10) { newP2Pos -= 10; }
                        int newP2Score = p2Score + newP2Pos;
                        if (newP2Score >= 21) {
                            scores.second += gameCount * outcomeCount;
                        }
                        else {
                            std::tuple<int, int, int, int, int> newState = { p1Pos, newP2Pos, p1Score, newP2Score, nextPlayer };
                            if (gameStates.contains(newState)) {
                                gameStates[newState] += gameCount * outcomeCount;
                            }
                            else {
                                gameStates[newState] = gameCount * outcomeCount;
                            }
                        }
                    }
                }
            }

            uint64_t result = std::max(scores.first, scores.second);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { result, endTime - startTime };
        }
    }
}