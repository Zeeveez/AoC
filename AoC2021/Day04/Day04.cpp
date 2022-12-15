#include "Day04.h"

#include <sstream>

namespace AoC2021 {
    namespace Day04 {
        std::pair<std::vector<int>, std::vector<std::vector<std::vector<int>>>> PreProcessInput(const std::vector<std::string>& input) {
            std::stringstream inputBingoNumbers(input[0]);
            std::string bingoNumber;
            std::vector<int> bingoNumbers = {};
            while (std::getline(inputBingoNumbers, bingoNumber, ',')) {
                bingoNumbers.push_back(std::stoi(bingoNumber));
            }

            std::vector<std::vector<std::vector<int>>> boards = {};
            int i = 1;
            while (i < input.size()) {
                boards.push_back({});
                for (int y = 0; y < 5; y++) {
                    boards[boards.size() - 1].push_back({});
                    for (int x = 0; x < 5; x++) {
                        boards[boards.size() - 1][y].push_back(std::stoi(input[i++]));
                    }
                }
            }

            return { bingoNumbers, boards };
        }

        bool CheckWin(const std::vector<std::vector<int>>& board) {
            for (int y = 0; y < 5; y++) {
                int sRow = 0;
                int sCol = 0;
                for (int x = 0; x < 5; x++) {
                    sRow += board[y][x];
                    sCol += board[x][y];
                }
                if (sRow == 0 || sCol == 0) {
                    return true;
                }
            }
            return false;
        }

        bool ApplyMove(std::vector<std::vector<int>>& board, int num) {
            for (int y = 0; y < 5; y++) {
                for (int x = 0; x < 5; x++) {
                    if (board[y][x] == num) {
                        board[y][x] = 0;
                        return true;
                    }
                }
            }
            return false;
        }

        int ScoreBoard(const std::vector<std::vector<int>>& board, int lastNum) {
            int s = 0;
            for (int y = 0; y < 5; y++) {
                for (int x = 0; x < 5; x++) {
                    s += board[y][x];
                }
            }
            return s * lastNum;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [numbers, boards] = PreProcessInput(input);

            for (auto& num : numbers) {
                for (auto& board : boards) {
                    if (ApplyMove(board, num) && CheckWin(board)) {
                        auto endTime = std::chrono::high_resolution_clock::now();
                        return { ScoreBoard(board, num), endTime - startTime };
                    }
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { 0, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [numbers, boards] = PreProcessInput(input);

            std::vector<std::vector<int>> winningBoard = {};
            std::vector<bool> won = {};
            int winningNumber = 0;
            while (won.size() < boards.size()) { won.push_back(false); }
            for (auto& num : numbers) {
                for (int i = 0; i < boards.size(); i++) {
                    if (!won[i] && ApplyMove(boards[i], num) && CheckWin(boards[i])) {
                        winningBoard = boards[i];
                        winningNumber = num;
                        won[i] = true;
                    }
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { ScoreBoard(winningBoard, winningNumber), endTime - startTime };
        }
    }
}