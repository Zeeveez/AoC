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
Times:
Day  1 - A: (    0.0623ms + 0.0328ms)
Day  1 - B: (    0.0430ms + 0.0328ms)
Day  2 - A: (    0.0096ms + 0.0002ms)
Day  2 - B: (    0.0287ms + 0.0002ms)
Day  3 - A: (    0.0010ms + 0.0343ms)
Day  3 - B: (    0.0015ms + 0.0343ms)
Day  4 - A: (    0.8182ms + 0.0002ms)
Day  4 - B: (    0.0914ms + 0.0002ms)
Day  5 - A: (    0.5021ms + 0.4122ms)
Day  5 - B: (    0.5845ms + 0.4122ms)
Day  6 - A: (    0.7274ms + 0.0406ms)
Day  6 - B: (   13.8940ms + 0.0406ms)
Day  7 - A: (    0.7530ms + 1.0683ms)
Day  7 - B: (   17.0904ms + 1.0683ms)
Day  8 - A: (    0.0082ms + 0.0152ms)
Day  8 - B: (    0.0133ms + 0.0152ms)
Day  9 - A: (    0.4356ms + 0.0001ms)
Day  9 - B: (   25.2765ms + 0.0001ms)
Day 10 - A: (    0.3038ms + 0.0004ms)
Day 10 - B: (    0.1462ms + 0.0004ms)
Day 11 - A: (    0.3174ms + 0.0002ms)
Day 11 - B: (   14.4061ms + 0.0002ms)
Day 12 - A: (   10.1681ms + 0.0004ms)
Day 12 - B: (   20.6453ms + 0.0004ms)
Day 13 - A: (    0.0023ms + 0.0394ms)
Day 13 - B: (    0.0019ms + 0.0394ms)
Day 14 - A: (    0.0049ms + 1.0636ms)
Day 14 - B: (    6.6477ms + 1.0636ms)
Day 15 - A: (    0.2840ms + 0.0995ms)
Day 15 - B: (    0.3219ms + 0.0995ms)
Day 16 - A: (   15.2692ms + 0.0003ms)
Day 16 - B: (   15.1235ms + 0.0003ms)
Day 17 - A: (    0.0010ms + 0.0319ms)
Day 17 - B: (   14.2166ms + 0.0319ms)
Day 18 - A: (    1.0219ms + 0.9268ms)
Day 18 - B: (    0.9740ms + 0.9268ms)
Day 19 - A: (    2.5491ms + 0.0713ms)
Day 19 - B: (   34.9081ms + 0.0713ms)
Day 20 - A: (    0.3544ms + 0.0003ms)
Day 20 - B: (   13.9410ms + 0.0003ms)
Day 21 - A: (    0.0453ms + 0.0002ms)
Day 21 - B: (    0.2459ms + 0.0002ms)
Day 22 - A: (    5.5085ms + 0.0001ms)
Day 22 - B: (   14.8530ms + 0.0001ms)
Day 23 - A: (    0.1422ms + 0.7544ms)
Day 23 - B: (    1.6200ms + 0.7544ms)
Day 24 - A: (    0.3054ms + 0.1884ms)
Day 24 - B: (    0.1059ms + 0.1884ms)
Day 25 - A: (    0.0259ms + 0.0286ms)
Day 25 - B: (    0.0003ms + 0.0286ms)

   Total A:     44.4305ms
   Total B:    199.9904ms
     Total:    239.6112ms
*/