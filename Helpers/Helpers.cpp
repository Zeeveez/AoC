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
                    { true, true, true, true },
                    { true, false, false, false },
                    { true, true, true, false },
                    { true, false, false, false },
                    { true, false, false, false },
                    { true, false, false, false }
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
                    { true, false, false, true },
                    { true, false, false, true },
                    { true, true, true, true },
                    { true, false, false, true },
                    { true, false, false, true },
                    { true, false, false, true }
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
                            if (kvp.second[y][x] != drawnString[i + x][y]) {
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

        std::string ParseDrawnString(const std::string& drawnString, int characters) {
            std::stringstream ss;
            for (int i = 0; i < characters * 5; i += 5) {
                bool found = false;
                for (auto& kvp : CHARACTERS) {
                    for (int x = 0; x < 4; x++) {
                        for (int y = 0; y < 6; y++) {
                            if (kvp.second[y][x] != (drawnString[i + x + y * characters * 5] == '#')) {
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
                            std::cout << drawnString[i + x + y * characters * 5];
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

        std::vector<int64_t> ReadCommaDelimitedList(std::string path) {
            std::fstream f(path);
            std::vector<int64_t> v = {};

            std::string line;
            f >> line;
            std::stringstream allInputs(line);
            std::vector<int64_t> inputs = {};
            std::string currentInput;
            while (std::getline(allInputs, currentInput, ',')) {
                inputs.push_back(std::stoll(currentInput));
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

        std::string Trim(const std::string& str) {
            size_t first = str.find_first_not_of(' ');
            if (std::string::npos == first) { return str; }
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }
    }
}