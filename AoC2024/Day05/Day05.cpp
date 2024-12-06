#include "Day05.h"

#include <regex>
#include <sstream>
#include <algorithm>

namespace AoC2024 {
    namespace Day05 {
        std::tuple<std::unordered_map<int, std::unordered_set<int>>, std::unordered_map<int, std::unordered_set<int>>, std::vector<std::vector<int>>> PreProcess(const std::vector<std::string>& input) {
            std::unordered_map<int, std::unordered_set<int>> whiteList = {};
            std::unordered_map<int, std::unordered_set<int>> blackList = {};
            std::vector<std::vector<int>> updates = {};

            static const std::regex re("(\\d+)\\|(\\d+)", std::regex::optimize);

            bool rules = true;
            for (auto& line : input) {
                if (line == "") { rules = false; continue; }

                if (rules) {
                    std::smatch sm;
                    if (std::regex_search(line, sm, re)) {
                        int before = std::stoi(sm[1]);
                        int after = std::stoi(sm[2]);

                        if (!whiteList.contains(before)) { whiteList[before] = {}; }
                        whiteList[before].insert(after);

                        if (!blackList.contains(after)) { blackList[after] = {}; }
                        blackList[after].insert(before);
                    }
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

        bool Check(const std::vector<std::string>& input, int x, int y, int sx, int sy, std::string target) {
            for (int i = 0; i < target.length(); i++) {
                int cx = x + sx * i;
                int cy = y + sy * i;
                if (cy < 0 || cy >= input.size()) { return false; }
                if (cx < 0 || cx >= input[cy].size()) { return false; }
                if (input[cy][cx] != target[i]) { return false; }
            }
            return true;
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