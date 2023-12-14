#ifndef DAY07_H
#define DAY07_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <set>

namespace AoC2023::Day07 {
    class Hand {
    public:
        std::vector<char> cards;
        std::unordered_map<char, int> cardCounts;
        std::set<char> uniqueCards;
        char type;
        uint64_t value;
        int bid;

        Hand() = default;
        Hand(const std::string& input, bool partB = false);

        void LoadValue(bool partB = false);
        void LoadUniqueCards(bool partB = false);
        void LoadCardCounts(bool partB = false);
        void LoadType(bool partB = false);

        bool FiveOfAKind(bool partB = false);
        bool FourOfAKind(bool partB = false);
        bool FullHouse(bool partB = false);
        bool ThreeOfAKind(bool partB = false);
        bool TwoPair(bool partB = false);
        bool OnePair(bool partB = false);

        friend bool operator<(const Hand& lhs, const Hand& rhs);
        friend bool operator>(const Hand& lhs, const Hand& rhs);
        friend bool operator<=(const Hand& lhs, const Hand& rhs);
        friend bool operator>=(const Hand& lhs, const Hand& rhs);
        friend bool operator==(const Hand& lhs, const Hand& rhs);
        friend bool operator!=(const Hand& lhs, const Hand& rhs);
    };

    std::vector<Hand> ParseInput(const std::vector<std::string>& input, bool partB = false);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif