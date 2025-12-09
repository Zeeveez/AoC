#include "AoC2024.h"

int main()
{
    AoC::Year<2024> year;
    year.days.push_back(AoC2024::Day01().Run());
    year.days.push_back(AoC2024::Day02().Run());
    year.days.push_back(AoC2024::Day03().Run());
    year.days.push_back(AoC2024::Day04().Run());
    year.days.push_back(AoC2024::Day05().Run());
    year.days.push_back(AoC2024::Day06().Run());
    year.days.push_back(AoC2024::Day07().Run());
    year.days.push_back(AoC2024::Day08().Run());
    year.days.push_back(AoC2024::Day09().Run());
    year.days.push_back(AoC2024::Day10().Run());
    year.days.push_back(AoC2024::Day11().Run());
    year.days.push_back(AoC2024::Day12().Run());
    year.days.push_back(AoC2024::Day13().Run());
    year.days.push_back(AoC2024::Day14().Run());
    year.days.push_back(AoC2024::Day15().Run());
    year.days.push_back(AoC2024::Day16().Run());
    year.days.push_back(AoC2024::Day17().Run());
    year.days.push_back(AoC2024::Day18().Run());
    year.days.push_back(AoC2024::Day19().Run());
    year.days.push_back(AoC2024::Day20().Run());
    year.days.push_back(AoC2024::Day21().Run());
    year.days.push_back(AoC2024::Day22().Run());
    year.days.push_back(AoC2024::Day23().Run());
    year.days.push_back(AoC2024::Day24().Run());
    year.days.push_back(AoC2024::Day25().Run());
    std::cout << year;
}