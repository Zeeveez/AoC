#ifndef DAY04_H
#define DAY04_H

#include <vector>
#include <string>
#include <iterator>
#include <chrono>

namespace AoC2021 {
    namespace Day04 {
        std::pair<std::vector<int>, std::vector<std::vector<std::vector<int>>>> PreProcessInput(const std::vector<std::string>& input);
        bool CheckWin(const std::vector<std::vector<int>>& board);
        bool ApplyMove(std::vector<std::vector<int>>& board, int num);
        int ScoreBoard(const std::vector<std::vector<int>>& board, int lastNum);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif