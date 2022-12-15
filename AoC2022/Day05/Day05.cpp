#include "Day05.h"

#include <regex>
#include <stack>

namespace AoC2022 {
    namespace Day05 {
        std::pair<std::vector<std::deque<char>>, std::vector<std::tuple<int, int, int>>> PreProcessInput(const std::vector<std::string>& lines) {
            std::vector<std::deque<char>> columns = {};
            columns.resize((lines[0].size() + 1) / 4);
            std::vector<std::tuple<int, int, int>> instructions = {};

            bool atHeader = true;
            for (auto& line : lines) {
                if (line == "" || line[1] == '1') {
                    atHeader = false;
                }
                else if (atHeader) {
                    for (int i = 1, col = 0; i < line.length(); i += 4, col++) {
                        if (line[i] != ' ') { columns[col].push_back(line[i]); }
                    }
                }
                else {
                    static const std::regex re("move (\\d+) from (\\d+) to (\\d+)", std::regex::optimize);
                    std::smatch sm;

                    if (std::regex_search(line, sm, re)) {
                        instructions.push_back(
                            {
                                std::stoi(sm[1]),
                                std::stoi(sm[2]),
                                std::stoi(sm[3])
                            });
                    }
                }
            }

            return { columns, instructions };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();
            auto [columns, instructions] = PreProcessInput(input);

            for (auto& ins : instructions) {
                int from = std::get<1>(ins) - 1;
                int to = std::get<2>(ins) - 1;
                for (int i = 0; i < std::get<0>(ins); i++) {
                    char val = columns[from].front(); columns[from].pop_front();
                    columns[to].push_front(val);
                }
            }

            std::string res = "";
            for (auto& col : columns) {
                res += col.front();
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [columns, instructions] = PreProcessInput(input);

            for (auto& ins : instructions) {
                int from = std::get<1>(ins) - 1;
                int to = std::get<2>(ins) - 1;

                std::stack<char> crates = {};
                for (int i = 0; i < std::get<0>(ins); i++) {
                    char val = columns[from].front(); columns[from].pop_front();
                    crates.push(val);
                }
                for (int i = 0; i < std::get<0>(ins); i++) {
                    columns[to].push_front(crates.top());
                    crates.pop();
                }
            }

            std::string res = "";
            for (auto& col : columns) {
                res += col.front();
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - startTime };
        }
    }
}