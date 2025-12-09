#include "AoC2019.h"

int main()
{
    AoC::Year<2019> year;
    year.days.push_back(AoC2019::Day01().Run());
    year.days.push_back(AoC2019::Day02().Run());
    year.days.push_back(AoC2019::Day03().Run());
    year.days.push_back(AoC2019::Day04().Run());
    year.days.push_back(AoC2019::Day05().Run());
    year.days.push_back(AoC2019::Day06().Run());
    year.days.push_back(AoC2019::Day07().Run());
    year.days.push_back(AoC2019::Day08().Run());
    year.days.push_back(AoC2019::Day09().Run());
    year.days.push_back(AoC2019::Day10().Run());
    year.days.push_back(AoC2019::Day11().Run());
    year.days.push_back(AoC2019::Day12().Run());
    year.days.push_back(AoC2019::Day13().Run());
    year.days.push_back(AoC2019::Day14().Run());
    year.days.push_back(AoC2019::Day15().Run());
    year.days.push_back(AoC2019::Day16().Run());
    year.days.push_back(AoC2019::Day17().Run());
    std::cout << year;
}