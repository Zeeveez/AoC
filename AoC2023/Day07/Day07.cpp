#include "Day07.h"

#include <iostream>

namespace AoC2023::Day07 {
    std::unordered_map<char, int> cardToValueMap = {
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

    Hand::Hand(const std::string& input, bool partB) {
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

    void Hand::LoadValue(bool partB) {
        value = 0;
        for (auto& c : cards) {
            value = value * 128 + cardToValueMap[c] + (partB && c == 'J' ? -10 : 0);
        }
        this->value = value;
    }

    void Hand::LoadUniqueCards(bool partB) {
        for (auto& c : cards) {
            uniqueCards.insert(c);
        }
    }

    void Hand::LoadCardCounts(bool partB) {
        for (auto& c : uniqueCards) {
            cardCounts[c] = 0;
        }
        for (auto& c : cards) {
            cardCounts[c]++;
        }
    }

    void Hand::LoadType(bool partB) {
        if (FiveOfAKind(partB)) { type = 6; }
        else if (FourOfAKind(partB)) { type = 5; }
        else if (FullHouse(partB)) { type = 4; }
        else if (ThreeOfAKind(partB)) { type = 3; }
        else if (TwoPair(partB)) { type = 2; }
        else if (OnePair(partB)) { type = 1; }
        else { type = 0; }
    }

    bool Hand::FiveOfAKind(bool partB) {
        for (auto& c : uniqueCards) {
            if (cardCounts[c] == 5) {
                return true;
            }
        }

        if (partB && cardCounts.contains('J')) {
            return uniqueCards.size() == 2;
        }

        return false;
    }

    bool Hand::FourOfAKind(bool partB) {
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

    bool Hand::FullHouse(bool partB) {
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

    bool Hand::ThreeOfAKind(bool partB) {
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

    bool Hand::TwoPair(bool partB) {
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

    bool Hand::OnePair(bool partB) {
        for (auto& c : uniqueCards) {
            if (cardCounts[c] == 2) {
                return true;
            }
        }
        return partB && uniqueCards.contains('J');
    }

    bool operator<(const Hand& lhs, const Hand& rhs) {
        if (lhs.type < rhs.type) {
            return true;
        }
        if (lhs.type > rhs.type) {
            return false;
        }
        return lhs.value < rhs.value;
    }

    bool operator>(const Hand& lhs, const Hand& rhs) {
        return rhs < lhs;
    }

    bool operator<=(const Hand& lhs, const Hand& rhs) {
        return !(lhs > rhs);
    }

    bool operator>=(const Hand& lhs, const Hand& rhs) {
        return !(lhs < rhs);
    }

    bool operator==(const Hand& lhs, const Hand& rhs) {
        return lhs.value == rhs.value;
    }

    bool operator!=(const Hand& lhs, const Hand& rhs) {
        return !(lhs == rhs);
    }

    std::vector<Hand> ParseInput(const std::vector<std::string>& input, bool partB) {
        std::vector<Hand> hands = {};
        for (auto& line : input) {
            hands.push_back(Hand(line, partB));
        }
        return hands;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto hands = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::sort(hands.begin(), hands.end());

        uint64_t score = 0;
        for (size_t i = 0; i < hands.size(); i++) {
            score += (i + 1) * hands[i].bid;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto hands = ParseInput(input, true);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::sort(hands.begin(), hands.end());

        uint64_t score = 0;
        for (size_t i = 0; i < hands.size(); i++) {
            score += (i + 1) * hands[i].bid;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}