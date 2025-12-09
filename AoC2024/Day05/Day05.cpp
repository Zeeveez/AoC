#include <sstream>
#include <algorithm>

#include "Day05.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day05::Parse() {
        bool rules = true;
        for (auto& line : rawData) {
            if (line == "") { rules = false; continue; }

            if (rules) {
                int before = (line[0] - '0') * 10 + line[1] - '0';
                int after = (line[3] - '0') * 10 + line[4] - '0';
                if (!whiteList.contains(before)) { whiteList[before] = {}; }
                whiteList[before].insert(after);

                if (!blackList.contains(after)) { blackList[after] = {}; }
                blackList[after].insert(before);
            }
            else {
                std::stringstream allInputs(line);
                std::vector<int> inputs = {};
                std::string currentInput;
                while (std::getline(allInputs, currentInput, ',')) {
                    inputs.push_back(std::stoi(currentInput));
                }
                updates.push_back(inputs);
            }
        }
    }

    AoC::DayResult::PuzzleResult Day05::A() {
        uint64_t res = 0;

        for (auto& update : updates) {
            std::unordered_set<int> blackListed = {};
            bool bad = false;
            for (auto& page : update) {
                if (blackListed.contains(page)) {
                    bad = true;
                    break;
                }
                blackListed.insert(blackList[page].begin(), blackList[page].end());
            }

            if (!bad) {
                res += update[update.size() / 2];
            }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day05::B() {
        uint64_t res = 0;

        for (auto& update : updates) {
            std::unordered_set<int> blackListed = {};
            bool bad = false;
            for (auto& page : update) {
                if (blackListed.contains(page)) {
                    bad = true;
                    break;
                }
                blackListed.insert(blackList[page].begin(), blackList[page].end());
            }

            if (bad) {
                std::sort(
                    update.begin(),
                    update.end(),
                    [&](int a, int b) {
                        return whiteList.contains(a) && whiteList[a].contains(b);
                    }
                );
                res += update[update.size() / 2];
            }
        }

        return res;
    }
}