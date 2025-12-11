#include "AoC2025.h"

int main()
{
    AoC::Year<2025> year;
    year.days.push_back(AoC2025::Day01().Run());
    year.days.push_back(AoC2025::Day02().Run());
    year.days.push_back(AoC2025::Day03().Run());
    year.days.push_back(AoC2025::Day04().Run());
    year.days.push_back(AoC2025::Day05().Run());
    year.days.push_back(AoC2025::Day06().Run());
    year.days.push_back(AoC2025::Day07().Run());
    year.days.push_back(AoC2025::Day08().Run());
    year.days.push_back(AoC2025::Day09().Run());
    year.days.push_back(AoC2025::Day11().Run());
    std::cout << year;
}