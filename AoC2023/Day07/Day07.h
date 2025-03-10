#pragma once
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day07 : public AoC::Day {
    private:
        class Hand {
        public:
            std::vector<char> cards;
            std::unordered_map<char, int> cardCounts;
            std::unordered_set<char> uniqueCards;
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

            friend bool operator<(const Hand& lhs, const Hand& rhs) {
                if (lhs.type < rhs.type) { return true; }
                if (lhs.type > rhs.type) { return false; }
                return lhs.value < rhs.value;
            }
            friend bool operator>(const Hand& lhs, const Hand& rhs) { return rhs < lhs; }
            friend bool operator<=(const Hand& lhs, const Hand& rhs) { return !(lhs > rhs); }
            friend bool operator>=(const Hand& lhs, const Hand& rhs) { return !(lhs < rhs); }
            friend bool operator==(const Hand& lhs, const Hand& rhs) { return lhs.value == rhs.value; }
            friend bool operator!=(const Hand& lhs, const Hand& rhs) { return !(lhs == rhs); }
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day07() : Day() {
            dayNo = 7;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};

        std::vector<Hand> ParseInput(const std::vector<std::string>& input, bool partB = false);
        uint64_t ScoreHands(std::vector<Hand>& hands);
    };
}