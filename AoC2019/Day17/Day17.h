#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day17 : public AoC::Day<std::vector<std::int64_t>, 2019, 17> {
    private:
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<std::vector<char>> GetMap(std::vector<std::int64_t> program);
        std::pair<std::pair<int, int>, std::pair<int, int>> GetPosAndDir(std::vector<std::vector<char>> scaffold);
        bool InRange(std::vector<std::vector<char>> scaffold, std::pair<int, int> pos, std::pair<int, int> dir);
        char GetDirChange(std::pair<int, int> dir, std::pair<int, int> newDir);
        std::string GetFullPath(std::vector<std::vector<char>> scaffold);
        int CountSubstring(std::string str, std::string substr);
        std::vector<std::string> SeparatePath(std::string path);
    };
}