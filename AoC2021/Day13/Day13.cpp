#include "Day13.h"

#include <algorithm>
#include <sstream>
#include "../../Helpers/Helpers.h"

namespace AoC2021 {
    namespace Day13 {
        std::pair<std::vector<std::vector<bool>>, std::vector<std::pair<char, int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<int, int>> points = {};
            int maxX = 0;
            int maxY = 0;

            std::vector<std::pair<char, int>> instructions = {};

            bool onPoints = true;
            for (auto& line : input) {
                if (line == "fold" || line == "along") { onPoints = false; continue; }
                if (onPoints) {
                    int x = std::stoi(line.substr(0, line.find(',')));
                    int y = std::stoi(line.substr(line.find(',') + 1));
                    maxX = std::max(x, maxX);
                    maxY = std::max(y, maxY);
                    points.push_back({ x, y });
                }
                else {
                    char axis = line[line.find('=') - 1];
                    int pos = std::stoi(line.substr(line.find('=') + 1));
                    instructions.push_back({ axis, pos });
                }
            }

            std::vector<std::vector<bool>> paper = {};
            for (int x = 0; x <= maxX; x++) {
                paper.push_back({});
                for (int y = 0; y <= maxY; y++) {
                    paper[x].push_back(false);
                }
            }
            for (auto& point : points) {
                paper[point.first][point.second] = true;
            }

            return { paper , instructions };
        }

        void Fold(std::vector<std::vector<bool>>& paper, std::pair<int, int>& widthHeight, const std::pair<char, int>& instruction) {
            if (instruction.first == 'x') {
                widthHeight.first = instruction.second;
                for (int x = 0; x < instruction.second; x++) {
                    if (instruction.second * 2 - x >= paper.size()) { continue; }
                    for (int y = 0; y < paper[x].size(); y++) {
                        paper[x][y] = paper[x][y] || paper[instruction.second * 2 - x][y];
                    }
                }
            }
            else {
                widthHeight.second = instruction.second;
                for (int x = 0; x < paper.size(); x++) {
                    for (int y = 0; y < instruction.second; y++) {
                        if (instruction.second * 2 - y >= paper[x].size()) { continue; }
                        paper[x][y] = paper[x][y] || paper[x][instruction.second * 2 - y];
                    }
                }
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [paper, instructions] = PreProcessInput(input);
            std::pair<int, int> widthHeight = { paper.size(), paper[0].size() };
            Fold(paper, widthHeight, instructions[0]);

            int c = 0;
            for (int x = 0; x < widthHeight.first; x++) {
                for (int y = 0; y < widthHeight.second; y++) {
                    c += paper[x][y];
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [paper, instructions] = PreProcessInput(input);
            std::pair<int, int> widthHeight = { paper.size(), paper[0].size() };

            for (auto& instruction : instructions) {
                Fold(paper, widthHeight, instruction);
            }

            std::string res = AoC::Helpers::ParseDrawnString(paper);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { res, endTime - startTime };
        }
    }
}