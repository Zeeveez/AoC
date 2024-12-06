#include "Day05.h"

#include <sstream>
#include <algorithm>

namespace AoC2024 {
    namespace Day05 {
        std::tuple<std::unordered_map<int, std::unordered_set<int>>, std::unordered_map<int, std::unordered_set<int>>, std::vector<std::vector<int>>> PreProcess(const std::vector<std::string>& input) {
            std::unordered_map<int, std::unordered_set<int>> whiteList = {};
            std::unordered_map<int, std::unordered_set<int>> blackList = {};
            std::vector<std::vector<int>> updates = {};

            bool rules = true;
            for (auto& line : input) {
                if (line == "") { rules = false; continue; }

                if (rules) {
                    int before = (line[1] - '0') * 10 + line[1] - '0';
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

            return { whiteList, blackList, updates };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [whiteList, blackList, updates] = PreProcess(input);

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

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [whiteList, blackList, updates] = PreProcess(input);

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
                        [&whiteList](int a, int b) {
                            return whiteList.contains(a) && whiteList[a].contains(b);
                        }
                    );
                    res += update[update.size() / 2];
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}