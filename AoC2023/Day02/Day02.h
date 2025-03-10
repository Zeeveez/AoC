#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day02 : public AoC::Day {
    private:
        enum class Color {
            RED,
            GREEN,
            BLUE
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day02() : Day() {
            dayNo = 2;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::vector<std::unordered_map<Color, int>>> games = {};

        std::pair<Color, int> ParseDraw(const std::string& line, size_t& i);
        std::unordered_map<Color, int> ParseRound(const std::string& line, size_t& i);
        std::vector<std::unordered_map<Color, int>> ParseGame(const std::string& line);
        std::vector<std::vector<std::unordered_map<Color, int>>> ParseInput(const std::vector<std::string>& input);
    };
}