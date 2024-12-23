#include "Helpers.h"

#include <sstream>

namespace AoC {
    namespace Helpers {
        std::unordered_map<char, std::vector<std::vector<bool>>> CHARACTERS = {
            { 'A',
                {
                    { false,  true,  true, false },
                    {  true, false, false,  true },
                    {  true, false, false,  true },
                    {  true,  true,  true,  true },
                    {  true, false, false,  true },
                    {  true, false, false,  true }
                }
            },
            { 'B',
                {
                    {  true,  true,  true, false },
                    {  true, false, false,  true },
                    {  true,  true,  true, false },
                    {  true, false, false,  true },
                    {  true, false, false,  true },
                    {  true,  true,  true, false }
                }
            },
            { 'C',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'D',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'E',
                {
                    {  true,  true,  true,  true },
                    {  true, false, false, false },
                    {  true,  true,  true, false },
                    {  true, false, false, false },
                    {  true, false, false, false },
                    {  true,  true,  true,  true }
                }
            },
            { 'F',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'G',
                {
                    { false,  true,  true, false },
                    {  true, false, false,  true },
                    {  true, false, false, false },
                    {  true, false,  true,  true },
                    {  true, false, false,  true },
                    { false,  true,  true,  true }
                }
            },
            { 'H',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'I',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'J',
                {
                    { false, false,  true,  true },
                    { false, false, false,  true },
                    { false, false, false,  true },
                    { false, false, false,  true },
                    {  true, false, false,  true },
                    { false,  true,  true, false }
                }
            },
            { 'K',
                {
                    {  true, false, false,  true },
                    {  true, false,  true, false },
                    {  true,  true, false, false },
                    {  true, false,  true, false },
                    {  true, false,  true, false },
                    {  true, false, false,  true }
                }
            },
            { 'L',
                {
                    {  true, false, false, false },
                    {  true, false, false, false },
                    {  true, false, false, false },
                    {  true, false, false, false },
                    {  true, false, false, false },
                    {  true,  true,  true,  true }
                }
            },
            { 'M',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'N',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'O',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'P',
                {
                    {  true,  true,  true, false },
                    {  true, false, false,  true },
                    {  true, false, false,  true },
                    {  true,  true,  true, false },
                    {  true, false, false, false },
                    {  true, false, false, false }
                }
            },
            { 'Q',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'R',
                {
                    {  true,  true,  true, false },
                    {  true, false, false,  true },
                    {  true, false, false,  true },
                    {  true,  true,  true, false },
                    {  true, false,  true, false },
                    {  true, false, false,  true }
                }
            },
            { 'S',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'T',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'U',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'V',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'W',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'X',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'Y',
                {
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false },
                    { false, false, false, false }
                }
            },
            { 'Z',
                {
                    {  true,  true,  true,  true },
                    { false, false, false,  true },
                    { false, false,  true, false },
                    { false,  true, false, false },
                    {  true, false, false, false },
                    {  true,  true,  true,  true }
                }
            }
        };

        std::string ParseDrawnString(const std::vector<std::vector<bool>>& drawnString) {
            std::stringstream ss;
            for (int i = 0; i < 40; i += 5) {
                bool found = false;
                for (auto& kvp : CHARACTERS) {
                    for (int x = 0; x < 4; x++) {
                        for (int y = 0; y < 6; y++) {
                            if (!kvp.second[y][x] == drawnString[i + x][y]) {
                                goto nextchar;
                            }
                        }
                    }
                    found = true;
                    ss << kvp.first;
                    break;
                nextchar:;
                }

                if (!found) {
                    std::cout << "\nUnknown Character:\n";
                    for (int y = 0; y < 6; y++) {
                        for (int x = 0; x < 4; x++) {
                            std::cout << (drawnString[i + x][y] ? '#' : ' ');
                        }
                        std::cout << "\n";
                    }
                    std::cout << "\n";
                    ss << '?';
                }
            }

            return ss.str();
        }

        std::vector<std::string> SplitString(std::string str, char sep) {
            std::vector<std::string> values = {};
            std::stringstream ss(str);
            std::string substr;
            while (std::getline(ss, substr, sep)) {
                values.push_back(substr);
            }

            return values;
        }

        std::vector<int> ReadCommaDelimitedList(std::string path) {
            std::fstream f(path);
            std::vector<int> v = {};

            std::string line;
            f >> line;
            std::stringstream allInputs(line);
            std::vector<int> inputs = {};
            std::string currentInput;
            while (std::getline(allInputs, currentInput, ',')) {
                inputs.push_back(std::stoi(currentInput));
            }
            return inputs;
        }

        std::vector<std::string> ReadLines(std::string path) {
            std::fstream f(path);
            std::vector<std::string> v = {};

            for (std::string line; std::getline(f, line); )
            {
                v.push_back(line);
            }

            return v;
        }
    }
}