// AoC2015.cpp : Defines the entry point for the application.
//

#include "AoC2022.h"

int main()
{
    //auto D01P1 = AoC2022::Day01::A(AoC::Helpers::ReadLines("./Day01.txt"));
    //std::cout << "Day 01 - A (" << std::format("{:10.4f}", D01P1.second.count()) << "ms): " << D01P1.first << "\n";
    //auto D01P2 = AoC2022::Day01::B(AoC::Helpers::ReadLines("./Day01.txt"));
    //std::cout << "Day 01 - B (" << std::format("{:10.4f}", D01P2.second.count()) << "ms): " << D01P2.first << "\n";

    //auto D02P1 = AoC2022::Day02::A(AoC::Helpers::ReadTokens<char>("./Day02.txt"));
    //std::cout << "Day 02 - A (" << std::format("{:10.4f}", D02P1.second.count()) << "ms): " << D02P1.first << "\n";
    //auto D02P2 = AoC2022::Day02::B(AoC::Helpers::ReadTokens<char>("./Day02.txt"));
    //std::cout << "Day 02 - B (" << std::format("{:10.4f}", D02P2.second.count()) << "ms): " << D02P2.first << "\n";

    //auto D03P1 = AoC2022::Day03::A(AoC::Helpers::ReadTokens<std::string>("./Day03.txt"));
    //std::cout << "Day 03 - A (" << std::format("{:10.4f}", D03P1.second.count()) << "ms): " << D03P1.first << "\n";
    //auto D03P2 = AoC2022::Day03::B(AoC::Helpers::ReadTokens<std::string>("./Day03.txt"));
    //std::cout << "Day 03 - B (" << std::format("{:10.4f}", D03P2.second.count()) << "ms): " << D03P2.first << "\n";

    auto D04P1 = AoC2022::Day04::A(AoC::Helpers::ReadLines("./Day04.txt"));
    std::cout << "Day 04 - A (" << std::format("{:10.4f}", D04P1.second.count()) << "ms): " << D04P1.first << "\n";
    auto D04P2 = AoC2022::Day04::B(AoC::Helpers::ReadLines("./Day04.txt"));
    std::cout << "Day 04 - B (" << std::format("{:10.4f}", D04P2.second.count()) << "ms): " << D04P2.first << "\n";

    //auto D05P1 = AoC2022::Day05::A(AoC::Helpers::ReadLines("./Day05.txt"));
    //std::cout << "Day 05 - A (" << std::format("{:10.4f}", D05P1.second.count()) << "ms): " << D05P1.first << "\n";
    //auto D05P2 = AoC2022::Day05::B(AoC::Helpers::ReadLines("./Day05.txt"));
    //std::cout << "Day 05 - B (" << std::format("{:10.4f}", D05P2.second.count()) << "ms): " << D05P2.first << "\n";

    //auto D06P1 = AoC2022::Day06::A(AoC::Helpers::ReadToken<std::string>("./Day06.txt"));
    //std::cout << "Day 06 - A (" << std::format("{:10.4f}", D06P1.second.count()) << "ms): " << D06P1.first << "\n";
    //auto D06P2 = AoC2022::Day06::B(AoC::Helpers::ReadToken<std::string>("./Day06.txt"));
    //std::cout << "Day 06 - B (" << std::format("{:10.4f}", D06P2.second.count()) << "ms): " << D06P2.first << "\n";

    //auto D07P1 = AoC2022::Day07::A(AoC::Helpers::ReadLines("./Day07.txt"));
    //std::cout << "Day 07 - A (" << std::format("{:10.4f}", D07P1.second.count()) << "ms): " << D07P1.first << "\n";
    //auto D07P2 = AoC2022::Day07::B(AoC::Helpers::ReadLines("./Day07.txt"));
    //std::cout << "Day 07 - B (" << std::format("{:10.4f}", D07P2.second.count()) << "ms): " << D07P2.first << "\n";

    //auto D08P1 = AoC2022::Day08::A(AoC::Helpers::ReadLines("./Day08.txt"));
    //std::cout << "Day 08 - A (" << std::format("{:10.4f}", D08P1.second.count()) << "ms): " << D08P1.first << "\n";
    //auto D08P2 = AoC2022::Day08::B(AoC::Helpers::ReadLines("./Day08.txt"));
    //std::cout << "Day 08 - B (" << std::format("{:10.4f}", D08P2.second.count()) << "ms): " << D08P2.first << "\n";

    //auto D09P1 = AoC2022::Day09::A(AoC::Helpers::ReadLines("./Day09.txt"));
    //std::cout << "Day 09 - A (" << std::format("{:10.4f}", D09P1.second.count()) << "ms): " << D09P1.first << "\n";
    //auto D09P2 = AoC2022::Day09::B(AoC::Helpers::ReadLines("./Day09.txt"));
    //std::cout << "Day 09 - B (" << std::format("{:10.4f}", D09P2.second.count()) << "ms): " << D09P2.first << "\n";

    //auto D10P1 = AoC2022::Day10::A(AoC::Helpers::ReadTokens<std::string>("./Day10.txt"));
    //std::cout << "Day 10 - A (" << std::format("{:10.4f}", D10P1.second.count()) << "ms): " << D10P1.first << "\n";
    //auto D10P2 = AoC2022::Day10::B(AoC::Helpers::ReadTokens<std::string>("./Day10.txt"));
    //std::cout << "Day 10 - B (" << std::format("{:10.4f}", D10P2.second.count()) << "ms): " << D10P2.first << "\n";

    //auto D11P1 = AoC2022::Day11::A(AoC::Helpers::ReadLines("./Day11.txt"));
    //std::cout << "Day 11 - A (" << std::format("{:10.4f}", D11P1.second.count()) << "ms): " << D11P1.first << "\n";
    //auto D11P2 = AoC2022::Day11::B(AoC::Helpers::ReadLines("./Day11.txt"));
    //std::cout << "Day 11 - B (" << std::format("{:10.4f}", D11P2.second.count()) << "ms): " << D11P2.first << "\n";

    //auto D12P1 = AoC2022::Day12::A(AoC::Helpers::ReadLines("./Day12.txt"));
    //std::cout << "Day 12 - A (" << std::format("{:10.4f}", D12P1.second.count()) << "ms): " << D12P1.first << "\n";
    //auto D12P2 = AoC2022::Day12::B(AoC::Helpers::ReadLines("./Day12.txt"));
    //std::cout << "Day 12 - B (" << std::format("{:10.4f}", D12P2.second.count()) << "ms): " << D12P2.first << "\n";

    //auto D13P1 = AoC2022::Day13::A(AoC::Helpers::ReadLines("./Day13.txt"));
    //std::cout << "Day 13 - A (" << std::format("{:10.4f}", D13P1.second.count()) << "ms): " << D13P1.first << "\n";
    //auto D13P2 = AoC2022::Day13::B(AoC::Helpers::ReadLines("./Day13.txt"));
    //std::cout << "Day 13 - B (" << std::format("{:10.4f}", D13P2.second.count()) << "ms): " << D13P2.first << "\n";

    //auto D14P1 = AoC2022::Day14::A(AoC::Helpers::ReadLines("./Day14.txt"));
    //std::cout << "Day 14 - A (" << std::format("{:10.4f}", D14P1.second.count()) << "ms): " << D14P1.first << "\n";
    //auto D14P2 = AoC2022::Day14::B(AoC::Helpers::ReadLines("./Day14.txt"));
    //std::cout << "Day 14 - B (" << std::format("{:10.4f}", D14P2.second.count()) << "ms): " << D14P2.first << "\n";

    //auto D15P1 = AoC2022::Day15::A(AoC::Helpers::ReadLines("./Day15.txt"));
    //std::cout << "Day 15 - A (" << std::format("{:10.4f}", D15P1.second.count()) << "ms): " << D15P1.first << "\n";
    //auto D15P2 = AoC2022::Day15::B(AoC::Helpers::ReadLines("./Day15.txt"));
    //std::cout << "Day 15 - B (" << std::format("{:10.4f}", D15P2.second.count()) << "ms): " << D15P2.first << "\n";

    //auto D16P1 = AoC2022::Day16::A(AoC::Helpers::ReadLines("./Day16.txt"));
    //std::cout << "Day 16 - A (" << std::format("{:10.4f}", D16P1.second.count()) << "ms): " << D16P1.first << "\n";
    //auto D16P2 = AoC2022::Day16::B(AoC::Helpers::ReadLines("./Day16.txt"));
    //std::cout << "Day 16 - B (" << std::format("{:10.4f}", D16P2.second.count()) << "ms): " << D16P2.first << "\n";

    //auto D17P1 = AoC2022::Day17::A(AoC::Helpers::ReadTokens<char>("./Day17.txt"));
    //std::cout << "Day 17 - A (" << std::format("{:10.4f}", D17P1.second.count()) << "ms): " << D17P1.first << "\n";
    //auto D17P2 = AoC2022::Day17::B(AoC::Helpers::ReadTokens<char>("./Day17.txt"));
    //std::cout << "Day 17 - B (" << std::format("{:10.4f}", D17P2.second.count()) << "ms): " << D17P2.first << "\n";

    //auto D18P1 = AoC2022::Day18::A(AoC::Helpers::ReadLines("./Day18.txt"));
    //std::cout << "Day 18 - A (" << std::format("{:10.4f}", D18P1.second.count()) << "ms): " << D18P1.first << "\n";
    //auto D18P2 = AoC2022::Day18::B(AoC::Helpers::ReadLines("./Day18.txt"));
    //std::cout << "Day 18 - B (" << std::format("{:10.4f}", D18P2.second.count()) << "ms): " << D18P2.first << "\n";

    //auto D19P1 = AoC2022::Day19::A(AoC::Helpers::ReadLines("./Day19.txt"));
    //std::cout << "Day 19 - A (" << std::format("{:10.4f}", D19P1.second.count()) << "ms): " << D19P1.first << "\n";
    //auto D19P2 = AoC2022::Day19::B(AoC::Helpers::ReadLines("./Day19.txt"));
    //std::cout << "Day 19 - B (" << std::format("{:10.4f}", D19P2.second.count()) << "ms): " << D19P2.first << "\n";

    //auto D20P1 = AoC2022::Day20::A(AoC::Helpers::ReadTokens<int>("./Day20.txt"));
    //std::cout << "Day 20 - A (" << std::format("{:10.4f}", D20P1.second.count()) << "ms): " << D20P1.first << "\n";
    //auto D20P2 = AoC2022::Day20::B(AoC::Helpers::ReadTokens<int>("./Day20.txt"));
    //std::cout << "Day 20 - B (" << std::format("{:10.4f}", D20P2.second.count()) << "ms): " << D20P2.first << "\n";

    //auto D21P1 = AoC2022::Day21::A(AoC::Helpers::ReadLines("./Day21.txt"));
    //std::cout << "Day 21 - A (" << std::format("{:10.4f}", D21P1.second.count()) << "ms): " << D21P1.first << "\n";
    //auto D21P2 = AoC2022::Day21::B(AoC::Helpers::ReadLines("./Day21.txt"));
    //std::cout << "Day 21 - B (" << std::format("{:10.4f}", D21P2.second.count()) << "ms): " << D21P2.first << "\n";

    auto D22P1 = AoC2022::Day22::A(AoC::Helpers::ReadLines("./Day22.txt"));
    std::cout << "Day 22 - A (" << std::format("{:10.4f}", D22P1.second.count()) << "ms): " << D22P1.first << "\n";
    auto D22P2 = AoC2022::Day22::B(AoC::Helpers::ReadLines("./Day22.txt"));
    std::cout << "Day 22 - B (" << std::format("{:10.4f}", D22P2.second.count()) << "ms): " << D22P2.first << "\n";

    //auto D23P1 = AoC2022::Day23::A(AoC::Helpers::ReadLines("./Day23.txt"));
    //std::cout << "Day 23 - A (" << std::format("{:10.4f}", D23P1.second.count()) << "ms): " << D23P1.first << "\n";
    //auto D23P2 = AoC2022::Day23::B(AoC::Helpers::ReadLines("./Day23.txt"));
    //std::cout << "Day 23 - B (" << std::format("{:10.4f}", D23P2.second.count()) << "ms): " << D23P2.first << "\n";

    auto D24P1 = AoC2022::Day24::A(AoC::Helpers::ReadLines("./Day24.txt"));
    std::cout << "Day 24 - A (" << std::format("{:10.4f}", D24P1.second.count()) << "ms): " << D24P1.first << "\n";
    auto D24P2 = AoC2022::Day24::B(AoC::Helpers::ReadLines("./Day24.txt"));
    std::cout << "Day 24 - B (" << std::format("{:10.4f}", D24P2.second.count()) << "ms): " << D24P2.first << "\n";

    auto D25P1 = AoC2022::Day25::A(AoC::Helpers::ReadLines("./Day25.txt"));
    std::cout << "Day 25 - A (" << std::format("{:10.4f}", D25P1.second.count()) << "ms): " << D25P1.first << "\n";
    auto D25P2 = AoC2022::Day25::B(AoC::Helpers::ReadLines("./Day25.txt"));
    std::cout << "Day 25 - B (" << std::format("{:10.4f}", D25P2.second.count()) << "ms): " << D25P2.first << "\n";
    
    auto total = //D01P1.second + D01P2.second
        //+ D02P1.second + D02P2.second
        //+ D03P1.second + D03P2.second
        //+ D04P1.second + D04P2.second
        //+ D05P1.second + D05P2.second
        //+ D06P1.second + D06P2.second
        //+ D07P1.second + D07P2.second
        //+ D08P1.second + D08P2.second
        //+ D09P1.second + D09P2.second
        //+ D10P1.second + D10P2.second
        //+ D11P1.second + D11P2.second
        //+ D12P1.second + D12P2.second
        //+ D13P1.second + D13P2.second
        //+ D14P1.second + D14P2.second
        //+ D15P1.second + D15P2.second
        //+ D16P1.second + D16P2.second
        //+ D17P1.second + D17P2.second
        //+ D18P1.second + D18P2.second
        //+ D19P1.second + D19P2.second
        //+ D20P1.second + D20P2.second
        //+ D21P1.second + D21P2.second
        + D22P1.second + D22P2.second
        //+ D23P1.second + D23P2.second
        + D24P1.second + D24P2.second
        + D25P1.second + D25P2.second;

    std::cout << "\nTotal Time: " << std::format("{:10.4f}", total.count()) << "ms\n";
}