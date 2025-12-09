#include <map>
#include <numeric>

#include "Day17.h"
#include "../IntCodeCPU/IntCodeCPU.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day17::A() {
        std::vector<std::vector<char>> scaffold = GetMap(rawData);
        int alignmentSum = 0;
        for (int y = 0; y < scaffold.size(); y++) {
            for (int x = 0; x < scaffold[0].size(); x++) {
                if (scaffold[y][x] == '#' && y > 0 && x > 0 && y < scaffold.size() - 1 && x < scaffold[0].size() - 1) {
                    {
                        if (scaffold[y][x + 1] == '#' && scaffold[y][x - 1] == '#' && scaffold[y + 1][x] == '#' && scaffold[y - 1][x] == '#') {
                            alignmentSum += x * y;
                        }
                    }
                }
            }
        }
        return alignmentSum;
    }

    AoC::DayResult::PuzzleResult Day17::B() {
        std::string fullPath = GetFullPath(GetMap(rawData));
        std::vector<std::string> paths = SeparatePath(fullPath);
        std::stringstream ss;
        ss << paths[0] << '\n' << paths[1] << '\n' << paths[2] << '\n' << paths[3] << "\nn\n";
        IntCodeCPU computer(rawData);
        computer.memory[0] = 2;
        for (const char& c : ss.str()) {
            computer.RunToInput();
            computer.Input(c);
        }
        computer.RunToEnd();
        return computer.Output();
    }

    std::vector<std::vector<char>> Day17::GetMap(std::vector<std::int64_t> program) {
        IntCodeCPU computer(program);
        std::vector<std::vector<char>> scaffold = { {} };
        while (!computer.halted) {
            computer.RunToOutput();
            switch (computer.Output()) {
            case 35:    // #
                scaffold[scaffold.size() - 1].push_back('#');
                break;
            case 46:    // .
                scaffold[scaffold.size() - 1].push_back('.');
                break;
            case 10:    // \n
                scaffold.push_back({});
                break;
            case 60:    // <
                scaffold[scaffold.size() - 1].push_back('<');
                break;
            case 62:    // >
                scaffold[scaffold.size() - 1].push_back('>');
                break;
            case 94:    // ^
                scaffold[scaffold.size() - 1].push_back('^');
                break;
            case 118:   // v
                scaffold[scaffold.size() - 1].push_back('v');
                break;
            }
        }
        scaffold.erase(std::remove_if(scaffold.begin(), scaffold.end(), [](std::vector<char> vec) {return vec.size() == 0; }), scaffold.end());
        return scaffold;
    }

    std::pair<std::pair<int, int>, std::pair<int, int>> Day17::GetPosAndDir(std::vector<std::vector<char>> scaffold) {
        for (int y = 0; y < scaffold.size(); y++) {
            for (int x = 0; x < scaffold[0].size(); x++) {
                if (scaffold[y][x] == '^') {
                    return { {x,y},{0,-1} };
                }
                else if (scaffold[y][x] == '>') {
                    return { {x,y},{1,0} };
                }
                else if (scaffold[y][x] == 'v') {
                    return { {x,y},{0,1} };
                }
                else if (scaffold[y][x] == '<') {
                    return { {x,y},{-1,0} };
                }
            }
        }
    }

    bool Day17::InRange(std::vector<std::vector<char>> scaffold, std::pair<int, int> pos, std::pair<int, int> dir) {
        return pos.second + dir.second > -1
            && pos.first + dir.first > -1
            && pos.second + dir.second < scaffold.size()
            && pos.first + dir.first < scaffold[0].size();
    }

    char Day17::GetDirChange(std::pair<int, int> dir, std::pair<int, int> newDir) {
        if (dir.first == 0) {
            if (dir.second == 1) {
                return newDir.first == 1 ? 'L' : 'R';
            }
            else {
                return newDir.first == 1 ? 'R' : 'L';
            }
        }
        else {
            if (dir.first == 1) {
                return newDir.second == 1 ? 'R' : 'L';
            }
            else {
                return newDir.second == 1 ? 'L' : 'R';
            }
        }
    }

    std::string Day17::GetFullPath(std::vector<std::vector<char>> scaffold) {
        std::pair<std::pair<int, int>, std::pair<int, int>> PosDir = GetPosAndDir(scaffold);
        std::vector<std::pair<int, int>> dirs = { {0,-1},{1,0},{0,1},{-1,0} };
        std::string output = "";
        while (true) {
            int movSteps = 0;
            while (InRange(scaffold, PosDir.first, PosDir.second) && scaffold[PosDir.first.second + PosDir.second.second][PosDir.first.first + PosDir.second.first] == '#') {
                movSteps++;
                PosDir.first.second += PosDir.second.second;
                PosDir.first.first += PosDir.second.first;
            }
            if (movSteps) {
                output += std::to_string(movSteps) + ',';
            }
            for (auto& dir : dirs) {
                if ((std::abs(PosDir.second.first) == 1 && dir.first == 0) || (std::abs(PosDir.second.second) == 1 && dir.second == 0)) {
                    if (InRange(scaffold, PosDir.first, dir) && scaffold[PosDir.first.second + dir.second][PosDir.first.first + dir.first] == '#') {
                        output += GetDirChange(PosDir.second, dir);
                        output += ',';
                        PosDir.second = dir;
                        break;
                    }
                }
            }
            if (scaffold[PosDir.first.second + PosDir.second.second][PosDir.first.first + PosDir.second.first] == '.') {
                break;
            }
        }
        return output.substr(0, output.length() - 1);
    }

    int Day17::CountSubstring(std::string str, std::string substr) {
        // From https://stackoverflow.com/a/22489298
        int occurrences = 0;
        std::string::size_type pos = 0;
        while ((pos = str.find(substr, pos)) != std::string::npos) {
            ++occurrences;
            pos += substr.length();
        }
        return occurrences;
    }

    std::vector<std::string> Day17::SeparatePath(std::string path) {
        std::string mainRoutine = "";
        std::string moveFunction1 = "";
        std::string moveFunction2 = "";
        std::string moveFunction3 = "";

        // find substrings

        mainRoutine = "A,A,B,C,A,C,B,C,A,B";
        moveFunction1 = "L,4,L,10,L,6";
        moveFunction2 = "L,6,L,4,R,8,R,8";
        moveFunction3 = "L,6,R,8,L,10,L,8,L,8";
        return { mainRoutine, moveFunction1, moveFunction2, moveFunction3 };
    }
}