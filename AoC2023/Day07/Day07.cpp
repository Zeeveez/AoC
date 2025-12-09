#include <numeric>
#include <algorithm>

#include "Day07.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day07::Load() {
        input = AoC::Helpers::ReadLines("./Day07.txt");
    }

    void Day07::Parse() {
        // No parsing required
    }

    void Day07::A() {
        auto hands = ParseInput(input);
        auto res = ScoreHands(hands);
        partAResult.first = res;
    }

    void Day07::B() {
        auto hands = ParseInput(input, true);
        auto res = ScoreHands(hands);
        partBResult.first = res;
    }

    uint64_t Day07::ScoreHands(std::vector<Day07::Hand>& hands) {
        std::sort(hands.begin(), hands.end());
        size_t hIdx = 1;
        return std::accumulate(
            hands.begin(),
            hands.end(),
            (uint64_t)0,
            [&hIdx](const uint64_t& acc, const Hand& h) {
                return acc + hIdx++ * h.bid;
            }
        );
    }

    const std::unordered_map<char, int> cardToValueMap = {
            { 'A', 14 },
            { 'K', 13 },
            { 'Q', 12 },
            { 'J', 11 },
            { 'T', 10 },
            { '9', 9 },
            { '8', 8 },
            { '7', 7 },
            { '6', 6 },
            { '5', 5 },
            { '4', 4 },
            { '3', 3 },
            { '2', 2 }
    };

    Day07::Hand::Hand(const std::string& input, bool partB) {
        std::istringstream iss(input);
        std::string cardsString;
        iss >> cardsString;
        cards = std::vector<char>(cardsString.begin(), cardsString.end());
        iss >> bid;
        LoadValue(partB);
        LoadUniqueCards(partB);
        LoadCardCounts(partB);
        LoadType(partB);
    }

    void Day07::Hand::LoadValue(bool partB) {
        value = 0;
        for (auto& c : cards) {
            value = value * 128 + cardToValueMap.at(c) + (partB && c == 'J') * -10;
        }
        this->value = value;
    }

    void Day07::Hand::LoadUniqueCards(bool partB) {
        for (auto& c : cards) {
            uniqueCards.insert(c);
        }
    }

    void Day07::Hand::LoadCardCounts(bool partB) {
        for (auto& c : uniqueCards) {
            cardCounts[c] = 0;
        }
        for (auto& c : cards) {
            cardCounts[c]++;
        }
    }

    void Day07::Hand::LoadType(bool partB) {
        if (FiveOfAKind(partB)) { type = 6; }
        else if (FourOfAKind(partB)) { type = 5; }
        else if (FullHouse(partB)) { type = 4; }
        else if (ThreeOfAKind(partB)) { type = 3; }
        else if (TwoPair(partB)) { type = 2; }
        else if (OnePair(partB)) { type = 1; }
        else { type = 0; }
    }

    bool Day07::Hand::FiveOfAKind(bool partB) {
        if (uniqueCards.size() == 1) { return true; }

        if (partB && cardCounts.contains('J')) {
            return uniqueCards.size() == 2;
        }

        return false;
    }

    bool Day07::Hand::FourOfAKind(bool partB) {
        for (auto& c : uniqueCards) {
            if (cardCounts[c] == 4) {
                return true;
            }
        }

        if (partB && cardCounts.contains('J')) {
            return ThreeOfAKind()
                || (TwoPair() && cardCounts['J'] >= 2);
        }
        return false;
    }

    bool Day07::Hand::FullHouse(bool partB) {
        if (uniqueCards.size() == 2) {
            for (auto& c : uniqueCards) {
                if (cardCounts[c] == 3) {
                    return true;
                }
            }
        }

        if (partB && cardCounts.contains('J')) {
            return ThreeOfAKind()
                || TwoPair();
        }

        return false;
    }

    bool Day07::Hand::ThreeOfAKind(bool partB) {
        for (auto& c : uniqueCards) {
            if (cardCounts[c] == 3) {
                return true;
            }
        }

        if (partB && cardCounts.contains('J')) {
            return OnePair();
        }

        return false;
    }

    bool Day07::Hand::TwoPair(bool partB) {
        bool firstPairFound = false;
        for (auto& c : uniqueCards) {
            if (cardCounts[c] == 2) {
                if (firstPairFound) {
                    return true;
                }
                firstPairFound = true;
            }
        }

        if (partB && cardCounts.contains('J')) {
            return OnePair()
                || cardCounts['J'] >= 2;
        }

        return false;
    }

    bool Day07::Hand::OnePair(bool partB) {
        for (auto& c : uniqueCards) {
            if (cardCounts[c] == 2) {
                return true;
            }
        }
        return partB && uniqueCards.contains('J');
    }

    std::vector<Day07::Hand> Day07::ParseInput(const std::vector<std::string>& input, bool partB) {
        std::vector<Hand> hands = {};
        for (auto& line : input) {
            hands.push_back(Hand(line, partB));
        }
        return hands;
    }
}