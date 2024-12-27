#include "AoC2024.h"

int main()
{
    std::vector<AoC::Day> days = {
        //AoC2024::Day01(),
        //AoC2024::Day02(),
        //AoC2024::Day03(),
        //AoC2024::Day04(),
        //AoC2024::Day05(),
        //AoC2024::Day06(),
        //AoC2024::Day07(),
        //AoC2024::Day08(),
        //AoC2024::Day09(),
        //AoC2024::Day10(),
        //AoC2024::Day11(),
        //AoC2024::Day12(),
        //AoC2024::Day13(),
        //AoC2024::Day14(),
        //AoC2024::Day15(),
        //AoC2024::Day16(),
        //AoC2024::Day17(),
        //AoC2024::Day18(),
        //AoC2024::Day19(),
        //AoC2024::Day20(),
        //AoC2024::Day21(),
        //AoC2024::Day22(),
        //AoC2024::Day23(),
        //AoC2024::Day24(),
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