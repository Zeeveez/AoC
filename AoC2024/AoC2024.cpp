#include "AoC2024.h"

int main()
{
    std::vector<AoC::Day> days = {
        AoC2024::Day01(),
        AoC2024::Day02(),
        AoC2024::Day03(),
        AoC2024::Day04(),
        AoC2024::Day05(),
        AoC2024::Day06(),
        AoC2024::Day07(),
        AoC2024::Day08(),
        AoC2024::Day09(),
        AoC2024::Day10(),
        AoC2024::Day11(),
        AoC2024::Day12(),
        AoC2024::Day13(),
        AoC2024::Day14(),
        AoC2024::Day15(),
        AoC2024::Day16(),
        AoC2024::Day17(),
        AoC2024::Day18(),
        AoC2024::Day19(),
        AoC2024::Day20(),
        AoC2024::Day21(),
        AoC2024::Day22(),
        AoC2024::Day23(),
        AoC2024::Day24(),
        AoC2024::Day25(),
    };

    std::chrono::duration<double, std::milli> totalATime = std::chrono::duration<double, std::milli>(0);
    std::chrono::duration<double, std::milli> totalBTime = std::chrono::duration<double, std::milli>(0);
    std::chrono::duration<double, std::milli> totalParseTime = std::chrono::duration<double, std::milli>(0);
    for (auto& day : days) {
        std::cout << day;
        totalParseTime += day.parseResult.second;
        totalATime += day.partAResult.second;
        totalBTime += day.partBResult.second;
    }

    std::cout << "\n";
    std::cout << "   Total A:  " << std::format("{:10.4f}", (totalATime + totalParseTime).count()) << "ms\n";
    std::cout << "   Total B:  " << std::format("{:10.4f}", (totalBTime + totalParseTime).count()) << "ms\n";
    std::cout << "     Total:  " << std::format("{:10.4f}", (totalATime + totalBTime + totalParseTime).count()) << "ms\n";
}

/*
Pre-Refine times:

Day  1 - A: (    0.0901ms +  0.0035ms)
Day  1 - B: (    0.1644ms +  0.0035ms)
Day  2 - A: (    0.0134ms +  0.0005ms)
Day  2 - B: (    0.0396ms +  0.0005ms)
Day  3 - A: (    0.0016ms +  3.0616ms)
Day  3 - B: (    0.0021ms +  3.0616ms)
Day  4 - A: (    1.0924ms +  0.0004ms)
Day  4 - B: (    0.0982ms +  0.0004ms)
Day  5 - A: (    0.6524ms +  0.5781ms)
Day  5 - B: (    0.6109ms +  0.5781ms)
Day  6 - A: (    0.8783ms +  0.0520ms)
Day  6 - B: (   14.0020ms +  0.0520ms)
Day  7 - A: (    0.7635ms +  1.1032ms)
Day  7 - B: (   18.3597ms +  1.1032ms)
Day  8 - A: (    0.0190ms +  0.0157ms)
Day  8 - B: (    0.0138ms +  0.0157ms)
Day  9 - A: (    0.6116ms +  0.0003ms)
Day  9 - B: (   52.9542ms +  0.0003ms)
Day 10 - A: (    0.3236ms +  0.0005ms)
Day 10 - B: (    0.1507ms +  0.0005ms)
Day 11 - A: (    0.4814ms +  0.0005ms)
Day 11 - B: (   16.6115ms +  0.0005ms)
Day 12 - A: (   12.8487ms +  0.0005ms)
Day 12 - B: (   21.4156ms +  0.0005ms)
Day 13 - A: (    0.0020ms +  0.0165ms)
Day 13 - B: (    0.0021ms +  0.0165ms)
Day 14 - A: (    0.0045ms +  1.0675ms)
Day 14 - B: (    6.8271ms +  1.0675ms)
Day 15 - A: (    0.2947ms +  0.0885ms)
Day 15 - B: (    0.3311ms +  0.0885ms)
Day 16 - A: (   17.3776ms +  0.0002ms)
Day 16 - B: (   16.6881ms +  0.0002ms)
Day 17 - A: (    0.0015ms +  0.0343ms)
Day 17 - B: (   14.3305ms +  0.0343ms)
Day 18 - A: (    1.0122ms +  1.0022ms)
Day 18 - B: (    1.0199ms +  1.0022ms)
Day 19 - A: (   11.2317ms +  0.0601ms)
Day 19 - B: (   94.0732ms +  0.0601ms)
Day 20 - A: (    0.3645ms +  0.0004ms)
Day 20 - B: (   16.8717ms +  0.0004ms)
Day 21 - A: (    0.0417ms +  0.0004ms)
Day 21 - B: (    0.2301ms +  0.0004ms)
Day 22 - A: (    5.6986ms +  0.0003ms)
Day 22 - B: (   15.1948ms +  0.0003ms)
Day 23 - A: (    0.1556ms +  0.7682ms)
Day 23 - B: (    1.5948ms +  0.7682ms)
Day 24 - A: (    0.3244ms +  0.1779ms)
Day 24 - B: (    0.1049ms +  0.1779ms)
Day 25 - A: (    0.0263ms +  0.0175ms)
Day 25 - B: (    0.0003ms +  0.0175ms)
*/