#include "Day04.h"

#include <iostream>

namespace AoC2023 {
    namespace Day04 {
        std::pair<std::set<int>, std::set<int>> ParseCard(const std::string& card) {
            std::istringstream iss(card);
            std::string token;
            iss >> token;   // Discard "Card"
            iss >> token;   // Discard "##:"

            std::set<int> winners = {};
            std::set<int> numbers = {};

            bool gettingWinners = true;
            while (iss >> token) {
                if (token == "|") {
                    gettingWinners = false;
                    continue;
                }

                int v = std::stoi(token);
                if (gettingWinners) {
                    winners.insert(v);
                }
                else {
                    numbers.insert(v);
                }
            }

            return { winners, numbers };
        }

        std::vector<std::pair<std::set<int>, std::set<int>>> ParseInput(const std::vector<std::string>& input) {
            std::vector<std::pair<std::set<int>, std::set<int>>> cards = {};
            for (auto& line : input) {
                cards.push_back(ParseCard(line));
            }
            return cards;
        }

        size_t GetWins(const std::pair<std::set<int>, std::set<int>>& card) {
            int winnerCount = 0;
            for (auto& number : card.second) {
                if (card.first.contains(number)) {
                    winnerCount++;
                }
            }
            return winnerCount;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto cards = ParseInput(input);

            uint64_t score = 0;
            for (auto& card : cards) {
                auto winnerCount = GetWins(card);
                if (winnerCount) {
                    score += std::pow(2, winnerCount - 1);
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto cards = ParseInput(input);

            std::vector<int> cardCounts = {};
            for (size_t i = 0; i < cards.size(); i++) {
                cardCounts.push_back(1);
            }
            for (size_t i = 0; i < cards.size(); i++) {
                auto winnerCount = GetWins(cards[i]);
                for (size_t j = 0; j < winnerCount; j++) {
                    cardCounts[i + j + 1] += cardCounts[i];
                }
            }

            uint64_t score = 0;
            for (size_t i = 0; i < cardCounts.size(); i++) {
                score += cardCounts[i];
            }


            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }
    }
}