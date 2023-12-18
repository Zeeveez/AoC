// AoC2015.cpp : Defines the entry point for the application.
//

#include "AoC2023.h"

void Output(int day, char part, std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> res) {
    std::cout
        << std::format("Day {:02} - {}: ({:10.4f}ms + {:10.4f}ms): ",
                       day,
                       part,
                       std::get<1>(res).count(),
                       std::get<2>(res).count())
        << std::get<0>(res) << "\n";

}

int main()
{
    std::cout << "Day ## - #: (  Parse Time +     Run Time):\n";
    std::cout << "-----------------------------------------\n";
    auto D01P1 = AoC2023::Day01::A(AoC::Helpers::ReadLines("./Day01.txt"));
    Output(1, 'A', D01P1);
    auto D01P2 = AoC2023::Day01::B(AoC::Helpers::ReadLines("./Day01.txt"));
    Output(1, 'B', D01P2);

    auto D02P1 = AoC2023::Day02::A(AoC::Helpers::ReadLines("./Day02.txt"));
    Output(2, 'A', D02P1);
    auto D02P2 = AoC2023::Day02::B(AoC::Helpers::ReadLines("./Day02.txt"));
    Output(2, 'B', D02P2);

    auto D03P1 = AoC2023::Day03::A(AoC::Helpers::ReadLines("./Day03.txt"));
    Output(3, 'A', D03P1);
    auto D03P2 = AoC2023::Day03::B(AoC::Helpers::ReadLines("./Day03.txt"));
    Output(3, 'B', D03P2);

    auto D04P1 = AoC2023::Day04::A(AoC::Helpers::ReadLines("./Day04.txt"));
    Output(4, 'A', D04P1);
    auto D04P2 = AoC2023::Day04::B(AoC::Helpers::ReadLines("./Day04.txt"));
    Output(4, 'B', D04P2);

    auto D05P1 = AoC2023::Day05::A(AoC::Helpers::ReadLines("./Day05.txt"));
    Output(5, 'A', D05P1);
    auto D05P2 = AoC2023::Day05::B(AoC::Helpers::ReadLines("./Day05.txt"));
    Output(5, 'B', D05P2);

    auto D06P1 = AoC2023::Day06::A(AoC::Helpers::ReadLines("./Day06.txt"));
    Output(6, 'A', D06P1);
    auto D06P2 = AoC2023::Day06::B(AoC::Helpers::ReadLines("./Day06.txt"));
    Output(06, 'B', D06P2);

    auto D07P1 = AoC2023::Day07::A(AoC::Helpers::ReadLines("./Day07.txt"));
    Output(07, 'A', D07P1);
    auto D07P2 = AoC2023::Day07::B(AoC::Helpers::ReadLines("./Day07.txt"));
    Output(07, 'B', D07P2);

    auto D08P1 = AoC2023::Day08::A(AoC::Helpers::ReadLines("./Day08.txt"));
    Output(8, 'A', D08P1);
    auto D08P2 = AoC2023::Day08::B(AoC::Helpers::ReadLines("./Day08.txt"));
    Output(8, 'B', D08P2);

    auto D09P1 = AoC2023::Day09::A(AoC::Helpers::ReadLines("./Day09.txt"));
    Output(9, 'A', D09P1);
    auto D09P2 = AoC2023::Day09::B(AoC::Helpers::ReadLines("./Day09.txt"));
    Output(9, 'B', D09P2);

    auto D10P1 = AoC2023::Day10::A(AoC::Helpers::ReadLines("./Day10.txt"));
    Output(10, 'A', D10P1);
    auto D10P2 = AoC2023::Day10::B(AoC::Helpers::ReadLines("./Day10.txt"));
    Output(10, 'B', D10P2);

    auto D11P1 = AoC2023::Day11::A(AoC::Helpers::ReadLines("./Day11.txt"));
    Output(11, 'A', D11P1);
    auto D11P2 = AoC2023::Day11::B(AoC::Helpers::ReadLines("./Day11.txt"));
    Output(11, 'B', D11P2);

    auto D12P1 = AoC2023::Day12::A(AoC::Helpers::ReadLines("./Day12.txt"));
    Output(12, 'A', D12P1);
    auto D12P2 = AoC2023::Day12::B(AoC::Helpers::ReadLines("./Day12.txt"));
    Output(12, 'B', D12P2);

    auto D13P1 = AoC2023::Day13::A(AoC::Helpers::ReadLines("./Day13.txt"));
    Output(13, 'A', D13P1);
    auto D13P2 = AoC2023::Day13::B(AoC::Helpers::ReadLines("./Day13.txt"));
    Output(13, 'B', D13P2);

    auto D14P1 = AoC2023::Day14::A(AoC::Helpers::ReadLines("./Day14.txt"));
    Output(14, 'A', D14P1);
    auto D14P2 = AoC2023::Day14::B(AoC::Helpers::ReadLines("./Day14.txt"));
    Output(14, 'B', D14P2);

    auto D15P1 = AoC2023::Day15::A(AoC::Helpers::ReadLines("./Day15.txt"));
    Output(15, 'A', D15P1);
    auto D15P2 = AoC2023::Day15::B(AoC::Helpers::ReadLines("./Day15.txt"));
    Output(15, 'B', D15P2);

    auto D16P1 = AoC2023::Day16::A(AoC::Helpers::ReadLines("./Day16.txt"));
    Output(16, 'A', D16P1);
    //auto D16P2 = AoC2023::Day16::B(AoC::Helpers::ReadLines("./Day16.txt"));
    //Output(16, 'B', D16P2);

    //auto D17P1 = AoC2023::Day17::A(AoC::Helpers::ReadLines("./Day17.txt"));
    //Output(17, 'A', D17P1);
    //auto D17P2 = AoC2023::Day17::B(AoC::Helpers::ReadLines("./Day17.txt"));
    //Output(17, 'B', D17P2);

    auto D18P1 = AoC2023::Day18::A(AoC::Helpers::ReadLines("./Day18.txt"));
    Output(18, 'A', D18P1);
    auto D18P2 = AoC2023::Day18::B(AoC::Helpers::ReadLines("./Day18.txt"));
    Output(18, 'B', D18P2);

    auto totalParseTime = std::get<1>(D01P1) + std::get<1>(D01P2)
        + std::get<1>(D02P1) + std::get<1>(D02P2)
        + std::get<1>(D03P1) + std::get<1>(D03P2)
        + std::get<1>(D04P1) + std::get<1>(D04P2)
        + std::get<1>(D05P1) + std::get<1>(D05P2)
        + std::get<1>(D06P1) + std::get<1>(D06P2)
        + std::get<1>(D07P1) + std::get<1>(D07P2)
        + std::get<1>(D08P1) + std::get<1>(D08P2)
        + std::get<1>(D09P1) + std::get<1>(D09P2)
        + std::get<1>(D10P1) + std::get<1>(D10P2)
        + std::get<1>(D11P1) + std::get<1>(D11P2)
        + std::get<1>(D12P1) + std::get<1>(D12P2)
        + std::get<1>(D13P1) + std::get<1>(D13P2)
        + std::get<1>(D14P1) + std::get<1>(D14P2)
        + std::get<1>(D15P1) + std::get<1>(D15P2)
        + std::get<1>(D16P1)/* + std::get<1>(D16P2)
        + std::get<1>(D17P1) + std::get<1>(D17P2)*/
        + std::get<1>(D18P1) + std::get<1>(D18P2);

    auto totalRunTime = std::get<2>(D01P1) + std::get<2>(D01P2)
        + std::get<2>(D02P1) + std::get<2>(D02P2)
        + std::get<2>(D03P1) + std::get<2>(D03P2)
        + std::get<2>(D04P1) + std::get<2>(D04P2)
        + std::get<2>(D05P1) + std::get<2>(D05P2)
        + std::get<2>(D06P1) + std::get<2>(D06P2)
        + std::get<2>(D07P1) + std::get<2>(D07P2)
        + std::get<2>(D08P1) + std::get<2>(D08P2)
        + std::get<2>(D09P1) + std::get<2>(D09P2)
        + std::get<2>(D10P1) + std::get<2>(D10P2)
        + std::get<2>(D11P1) + std::get<2>(D11P2)
        + std::get<2>(D12P1) + std::get<2>(D12P2)
        + std::get<2>(D13P1) + std::get<2>(D13P2)
        + std::get<2>(D14P1) + std::get<2>(D14P2)
        + std::get<2>(D15P1) + std::get<2>(D15P2)
        + std::get<2>(D16P1)/* + std::get<2>(D16P2)
        + std::get<1>(D17P1) + std::get<1>(D17P2)*/
        + std::get<2>(D18P1) + std::get<2>(D18P2);


    std::cout << std::format("\n    Totals:  {:10.4f}ms + {:10.4f}ms : {:.4f}ms\n",
                             totalParseTime.count(),
                             totalRunTime.count(),
                             (totalParseTime + totalRunTime).count());
}