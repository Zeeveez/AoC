// AoC2015.cpp : Defines the entry point for the application.
//

#include "AoC2023.h"

int main()
{
    auto D01P1 = AoC2023::Day01::A(AoC::Helpers::ReadLines("./Day01.txt"));
    std::cout << "Day 01 - A (" << std::format("{:10.4f}", D01P1.second.count()) << "ms): " << D01P1.first << "\n";
    auto D01P2 = AoC2023::Day01::B(AoC::Helpers::ReadLines("./Day01.txt"));
    std::cout << "Day 01 - B (" << std::format("{:10.4f}", D01P2.second.count()) << "ms): " << D01P2.first << "\n";

    auto D02P1 = AoC2023::Day02::A(AoC::Helpers::ReadLines("./Day02.txt"));
    std::cout << "Day 02 - A (" << std::format("{:10.4f}", D02P1.second.count()) << "ms): " << D02P1.first << "\n";
    auto D02P2 = AoC2023::Day02::B(AoC::Helpers::ReadLines("./Day02.txt"));
    std::cout << "Day 02 - B (" << std::format("{:10.4f}", D02P2.second.count()) << "ms): " << D02P2.first << "\n";

    auto D03P1 = AoC2023::Day03::A(AoC::Helpers::ReadLines("./Day03.txt"));
    std::cout << "Day 03 - A (" << std::format("{:10.4f}", D03P1.second.count()) << "ms): " << D03P1.first << "\n";
    auto D03P2 = AoC2023::Day03::B(AoC::Helpers::ReadLines("./Day03.txt"));
    std::cout << "Day 03 - B (" << std::format("{:10.4f}", D03P2.second.count()) << "ms): " << D03P2.first << "\n";

    auto D04P1 = AoC2023::Day04::A(AoC::Helpers::ReadLines("./Day04.txt"));
    std::cout << "Day 04 - A (" << std::format("{:10.4f}", D04P1.second.count()) << "ms): " << D04P1.first << "\n";
    auto D04P2 = AoC2023::Day04::B(AoC::Helpers::ReadLines("./Day04.txt"));
    std::cout << "Day 04 - B (" << std::format("{:10.4f}", D04P2.second.count()) << "ms): " << D04P2.first << "\n";

    auto D05P1 = AoC2023::Day05::A(AoC::Helpers::ReadLines("./Day05.txt"));
    std::cout << "Day 05 - A (" << std::format("{:10.4f}", D05P1.second.count()) << "ms): " << D05P1.first << "\n";
    auto D05P2 = AoC2023::Day05::B(AoC::Helpers::ReadLines("./Day05.txt"));
    std::cout << "Day 05 - B (" << std::format("{:10.4f}", D05P2.second.count()) << "ms): " << D05P2.first << "\n";

    auto D06P1 = AoC2023::Day06::A(AoC::Helpers::ReadLines("./Day06.txt"));
    std::cout << "Day 06 - A (" << std::format("{:10.4f}", D06P1.second.count()) << "ms): " << D06P1.first << "\n";
    auto D06P2 = AoC2023::Day06::B(AoC::Helpers::ReadLines("./Day06.txt"));
    std::cout << "Day 06 - B (" << std::format("{:10.4f}", D06P2.second.count()) << "ms): " << D06P2.first << "\n";

    auto D07P1 = AoC2023::Day07::A(AoC::Helpers::ReadLines("./Day07.txt"));
    std::cout << "Day 07 - A (" << std::format("{:10.4f}", D07P1.second.count()) << "ms): " << D07P1.first << "\n";
    auto D07P2 = AoC2023::Day07::B(AoC::Helpers::ReadLines("./Day07.txt"));
    std::cout << "Day 07 - B (" << std::format("{:10.4f}", D07P2.second.count()) << "ms): " << D07P2.first << "\n";

    auto total = D01P1.second + D01P2.second
        + D02P1.second + D02P2.second
        + D03P1.second + D03P2.second
        + D04P1.second + D04P2.second
        + D05P1.second + D05P2.second
        + D06P1.second + D06P2.second
        + D07P1.second + D07P2.second;

    std::cout << "\nTotal Time: " << std::format("{:10.4f}", total.count()) << "ms\n";
}