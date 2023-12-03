#include "Day03.h"

namespace AoC2023 {
    namespace Day03 {
        std::vector<std::pair<size_t, size_t>> GetNeighbours(size_t x, size_t y, const std::vector<std::string>& input) {
            std::vector<std::pair<size_t, size_t>> neighbours = {};
            for (int dx = -1; dx < 2; dx++) {
                for (int dy = -1; dy < 2; dy++) {
                    if (dx == 0 && dy == 0) { continue; }
                    if (y + dy >= 0 && y + dy < input.size() && x + dx >= 0 && x + dx < input[y + dy].length()) {
                        neighbours.push_back({ x + dx, y + dy });
                    }
                }
            }
            return neighbours;
        }

        void RegisterPartNo(std::map<std::pair<size_t, size_t>, std::vector<int>>& partNoLists, char partType, std::pair<size_t, size_t> partPos, size_t partNo) {
            if (partNo > 0 && partType != '\0') {
                if (!partNoLists.contains(partPos)) {
                    partNoLists[partPos] = {};
                }
                partNoLists[partPos].push_back(partNo);
            }
        }

        std::map<std::pair<size_t, size_t>, std::vector<int>> GetPartNumberLists(const std::vector<std::string>& input) {
            std::map<std::pair<size_t, size_t>, std::vector<int>> partNoLists = {};

            for (size_t y = 0; y < input.size(); y++) {
                std::pair<size_t, size_t> partPos = { 0, 0 };
                char partType = '\0';
                size_t partNo = 0;
                for (size_t x = 0; x < input[y].length(); x++) {
                    if (input[y][x] >= '0' && input[y][x] <= '9') {
                        partNo = partNo * 10 + input[y][x] - '0';
                        for (auto& neighbour : GetNeighbours(x, y, input)) {
                            char v = input[neighbour.second][neighbour.first];
                            if (v != '.' && !(v >= '0' && v <= '9')) {
                                partPos = neighbour;
                                partType = v;
                            }
                        }
                    }

                    else {
                        RegisterPartNo(partNoLists, partType, partPos, partNo);
                        partType = '\0';
                        partNo = 0;
                    }
                }

                RegisterPartNo(partNoLists, partType, partPos, partNo);
                partType = '\0';
                partNo = 0;
            }

            return partNoLists;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            uint64_t score = 0;
            auto partNoLists = GetPartNumberLists(input);

            for (auto& kvp : partNoLists) {
                for (auto& part : kvp.second) {
                    score += part;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t score = 0;
            auto partNoLists = GetPartNumberLists(input);

            for (auto& kvp : partNoLists) {
                if (input[kvp.first.second][kvp.first.first] == '*' && kvp.second.size() == 2) {
                    score += kvp.second[0] * kvp.second[1];
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }
    }
}