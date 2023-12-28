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
    auto D12P1 = AoC2023::Day12::A(AoC::Helpers::ReadLines("./Day12.txt"));
    Output(12, 'A', D12P1);
    auto D12P2 = AoC2023::Day12::B(AoC::Helpers::ReadLines("./Day12.txt"));
    Output(12, 'B', D12P2);
}