#include "AoC2023.h"

int main()
{
    std::vector<AoC::Day> days = {
        AoC2023::Day01(),
        AoC2023::Day02(),
        AoC2023::Day03(),
        AoC2023::Day04(),
        AoC2023::Day05(),
        AoC2023::Day06(),
        AoC2023::Day07(),
        AoC2023::Day08(),
        AoC2023::Day09(),
        AoC2023::Day10(),
        AoC2023::Day11(),
        AoC2023::Day12(),
        AoC2023::Day13(),
        AoC2023::Day14(),
        AoC2023::Day15(),
        //AoC2023::Day16(), // SLOW
        //AoC2023::Day17(), // VERY SLOW
        //AoC2023::Day18(),
        //AoC2023::Day19(),
        //AoC2023::Day20(),
        //AoC2023::Day21(),
        AoC2023::Day22(),
        AoC2023::Day23(),
        AoC2023::Day24(),
        AoC2023::Day25(),
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
*/