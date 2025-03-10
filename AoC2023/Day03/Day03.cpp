#include "Day03.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    std::vector<std::pair<int, int>> dirs = {
        { -1, -1 },
        { 0, -1 },
        { 1, -1 },
        { -1, 0 },
        { 1, 0 },
        { -1, 1 },
        { 0, 1 },
        { 1, 1 }
    };

    void Day03::Load() {
        input = AoC::Helpers::ReadLines("./Day03.txt");
    }

    void Day03::Parse() {
        partNoLists = GetPartNumberLists(input);
    }

    void Day03::A() {
        uint64_t res = 0;
        for (auto& kvp : partNoLists) {
            for (auto& part : kvp.second) {
                res += part;
            }
        }
        partAResult.first = res;
    }

    void Day03::B() {
        uint64_t res = 0;
        for (auto& kvp : partNoLists) {
            if (input[kvp.first.second][kvp.first.first] == '*' && kvp.second.size() == 2) {
                res += kvp.second[0] * kvp.second[1];
            }
        }
        partBResult.first = res;
    }

    std::vector<std::pair<size_t, size_t>> Day03::GetNeighbours(size_t x, size_t y, const std::vector<std::string>& input) {
        std::vector<std::pair<size_t, size_t>> neighbours = {};
        for (auto& [dx, dy] : dirs) {
            if (y + dy >= 0 && y + dy < input.size() && x + dx >= 0 && x + dx < input[y + dy].length()) {
                neighbours.push_back({ x + dx, y + dy });
            }
        }
        return neighbours;
    }

    void Day03::RegisterPartNo(std::map<std::pair<size_t, size_t>, std::vector<int>>& partNoLists, char partType, std::pair<size_t, size_t> partPos, size_t partNo) {
        if (partNo > 0 && partType != '\0') {
            if (!partNoLists.contains(partPos)) {
                partNoLists[partPos] = {};
            }
            partNoLists[partPos].push_back(partNo);
        }
    }

    std::map<std::pair<size_t, size_t>, std::vector<int>> Day03::GetPartNumberLists(const std::vector<std::string>& input) {
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
}