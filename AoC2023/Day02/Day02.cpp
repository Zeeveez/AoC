#include <algorithm>

#include "Day02.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day02::Load() {
        input = AoC::Helpers::ReadLines("./Day02.txt");
    }

    void Day02::Parse() {
        games = ParseInput(input);
    }

    void Day02::A() {
        size_t res = 0;
        for (size_t i = 0; i < games.size(); i++) {
            for (auto& round : games[i]) {
                size_t reds = round.contains(Color::RED) ? round[Color::RED] : 0;
                size_t greens = round.contains(Color::GREEN) ? round[Color::GREEN] : 0;
                size_t blues = round.contains(Color::BLUE) ? round[Color::BLUE] : 0;
                if (reds > 12 || greens > 13 || blues > 14) {
                    goto bad_round;
                }
            }
            res += i + 1;
        bad_round:;
        }
        partAResult.first = res;
    }

    void Day02::B() {
        size_t res = 0;
        for (size_t i = 0; i < games.size(); i++) {
            std::unordered_map<Color, int> mins = {
                { Color::RED, 0 },
                { Color::GREEN, 0 },
                { Color::BLUE, 0 },
            };
            for (auto& round : games[i]) {
                mins[Color::RED] = std::max(mins[Color::RED], round.contains(Color::RED) ? round[Color::RED] : 0);
                mins[Color::GREEN] = std::max(mins[Color::GREEN], round.contains(Color::GREEN) ? round[Color::GREEN] : 0);
                mins[Color::BLUE] = std::max(mins[Color::BLUE], round.contains(Color::BLUE) ? round[Color::BLUE] : 0);
            }

            res += mins[Color::RED] * mins[Color::GREEN] * mins[Color::BLUE];
        }
        partBResult.first = res;
    }


    std::pair<Day02::Color, int> Day02::ParseDraw(const std::string& line, size_t& i) {
        int count = 0;
        while (line[i] >= '0' && line[i] <= '9') {
            count = count * 10 + line[i++] - '0';
        }

        Color color = Color::RED;
        while (i < line.length() && line[i] != ',' && line[i] != ';') { i++; }
        switch (line[i - 1]) {
        case 'e':
            color = Color::BLUE;
            break;
        case 'd':
            color = Color::RED;
            break;
        case 'n':
            color = Color::GREEN;
            break;
        }

        return { color, count };
    }

    std::unordered_map<Day02::Color, int> Day02::ParseRound(const std::string& line, size_t& i) {
        std::unordered_map<Color, int> draws = {};
        while (i < line.length() && line[i] != ';') {
            auto draw = ParseDraw(line, i);
            draws[draw.first] = draw.second;
            if (i >= line.length() || line[i] == ';') {
                break;
            }
            i += 2;
        }
        i += 2;
        return draws;
    }

    std::vector<std::unordered_map<Day02::Color, int>> Day02::ParseGame(const std::string& line) {
        std::vector<std::unordered_map<Color, int>> rounds = {};
        size_t i = line.find(':') + 2;
        while (i <= line.length()) {
            rounds.push_back(ParseRound(line, i));
            int t = 0;
        }
        return rounds;
    }

    std::vector<std::vector<std::unordered_map<Day02::Color, int>>> Day02::ParseInput(const std::vector<std::string>& input) {
        std::vector<std::vector<std::unordered_map<Color, int>>> games = {};
        for (auto& line : input) {
            games.push_back(ParseGame(line));
        }
        return games;
    }
}