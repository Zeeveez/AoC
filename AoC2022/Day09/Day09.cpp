#include "Day09.h"

#include <set>

namespace AoC2022 {
    namespace Day09 {
        std::vector<std::pair<std::pair<int, int>, int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<std::pair<int, int>, int>> instructions = {};
            for (auto& line : input) {
                switch (line[0]) {
                case 'U':
                    instructions.push_back(
                        {
                            { 0, 1 },
                            std::stoi(line.substr(2))
                        });
                    break;
                case 'D':
                    instructions.push_back(
                        {
                            { 0, -1 },
                            std::stoi(line.substr(2))
                        });
                    break;
                case 'L':
                    instructions.push_back(
                        {
                            { -1, 0 },
                            std::stoi(line.substr(2))
                        });
                    break;
                case 'R':
                    instructions.push_back(
                        {
                            { 1, 0 },
                            std::stoi(line.substr(2))
                        });
                    break;
                }
            }
            return instructions;
        }

        int HashPair(std::pair<int, int>& p) {
            return p.second * 2000 + p.first;
        }

        void Follow(std::pair<int, int>* head, std::pair<int, int>* tail) {
            if (head->first == tail->first + 2) {
                tail->first++;
                if (head->second != tail->second) {
                    tail->second += tail->second < head->second ? 1 : -1;
                }
            }
            else if (head->first == tail->first - 2) {
                tail->first--;
                if (head->second != tail->second) {
                    tail->second += tail->second < head->second ? 1 : -1;
                }
            }
            else if (head->second == tail->second + 2) {
                tail->second++;
                if (head->first != tail->first) {
                    tail->first += tail->first < head->first ? 1 : -1;
                }
            }
            else if (head->second == tail->second - 2) {
                tail->second--;
                if (head->first != tail->first) {
                    tail->first += tail->first < head->first ? 1 : -1;
                }
            }
        }

        uint64_t Run(const std::vector<std::string>& input, int segments) {
            auto instructions = PreProcessInput(input);

            std::vector<std::pair<int, int>> parts = { };
            for (int i = 0; i < segments; i++) {
                parts.push_back({ 1000, 1000 });
            }

            std::set<int> tailVisited = { HashPair(parts[parts.size() - 1]) };

            for (auto& instruction : instructions) {
                for (int i = 0; i < instruction.second; i++) {
                    parts[0].first += instruction.first.first;
                    parts[0].second += instruction.first.second;

                    for (int i = 0; i < segments - 1; i++) {
                        Follow(&parts[i], &parts[i + 1]);
                    }
                    tailVisited.insert(HashPair(parts[parts.size() - 1]));
                }
            }

            return tailVisited.size();
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto result = Run(input, 2);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { result, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto result = Run(input, 10);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { result, endtime - starttime };
        }
    }
}