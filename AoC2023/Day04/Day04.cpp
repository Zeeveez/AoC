#include "Day04.h"

#include <cmath>

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day04::Load() {
        input = AoC::Helpers::ReadLines("./Day04.txt");
    }

    void Day04::Parse() {
        cards = ParseInput(input);
    }

    void Day04::A() {
        uint64_t res = 0;
        for (auto& card : cards) {
            auto winnerCount = GetWins(card);
            if (winnerCount) {
                res += std::pow(2, winnerCount - 1);
            }
        }
        partAResult.first = res;
    }

    void Day04::B() {
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

        uint64_t res = 0;
        for (size_t i = 0; i < cardCounts.size(); i++) {
            res += cardCounts[i];
        }

        partBResult.first = res;
    }

    size_t Day04::GetWins(const std::pair<std::set<int>, std::set<int>>& card) {
        int winnerCount = 0;
        for (auto& number : card.second) {
            if (card.first.contains(number)) {
                winnerCount++;
            }
        }
        return winnerCount;
    }

    std::pair<std::set<int>, std::set<int>> Day04::ParseCard(const std::string& card) {
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

    std::vector<std::pair<std::set<int>, std::set<int>>> Day04::ParseInput(const std::vector<std::string>& input) {
        std::vector<std::pair<std::set<int>, std::set<int>>> cards = {};
        for (auto& line : input) {
            cards.push_back(ParseCard(line));
        }
        return cards;
    }
}