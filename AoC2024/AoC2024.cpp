#include "AoC2024.h"

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();

    //std::cout << AoC2024::Day01();
    //std::cout << AoC2024::Day02();
    //std::cout << AoC2024::Day03();
    //std::cout << AoC2024::Day04();
    //std::cout << AoC2024::Day05();
    //std::cout << AoC2024::Day06();
    //std::cout << AoC2024::Day07();
    //std::cout << AoC2024::Day08();
    //std::cout << AoC2024::Day09();
    //std::cout << AoC2024::Day10();
    //std::cout << AoC2024::Day11();
    //std::cout << AoC2024::Day12();
    //std::cout << AoC2024::Day13();
    //std::cout << AoC2024::Day14();
    //std::cout << AoC2024::Day15();
    //std::cout << AoC2024::Day16();
    //std::cout << AoC2024::Day17();
    //std::cout << AoC2024::Day18();
    //std::cout << AoC2024::Day19();
    //std::cout << AoC2024::Day20();
    std::cout << AoC2024::Day21();
    //std::cout << AoC2024::Day22();
    //std::cout << AoC2024::Day23();
    //std::cout << AoC2024::Day24();
    //std::cout << AoC2024::Day25();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = endTime - startTime;

    //std::cout << "\nTotal Time: " << std::format("{:10.4f}", total.count()) << "ms\n";
    std::cout << "Total Time (w/ I/O): " << std::format("{:10.4f}", duration.count()) << "ms\n";
}