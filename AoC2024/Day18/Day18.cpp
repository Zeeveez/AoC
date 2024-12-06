#include "Day18.h"

#include <regex>
#include <queue>
#include <tuple>
#include <set>

namespace AoC2022 {
    namespace Day18 {
        static std::vector<std::tuple<int, int, int>> neighbours = {
            { 0, 0, 1 },
            { 0, 0, -1 },
            { 0, 1, 0 },
            { 0, -1, 0 },
            { 1, 0, 0 },
            { -1, 0, 0 },
        };

        std::vector<std::vector<std::vector<State>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<std::vector<State>>> droplet = {};
            for (int x = 0; x < 25; x++) {
                droplet.push_back({});
                for (int y = 0; y < 25; y++) {
                    droplet[x].push_back({});
                    for (int z = 0; z < 25; z++) {
                        droplet[x][y].push_back(State::EMPTY);
                    }
                }
            }

            for (auto& line : input) {
                const std::regex cubeRe("(\\d+),(\\d+),(\\d+)");
                std::smatch sm;
                std::regex_search(line, sm, cubeRe);
                int x = std::stoi(sm[1]);
                int y = std::stoi(sm[2]);
                int z = std::stoi(sm[3]);

                while (!droplet.size() > x) { droplet.push_back({}); }
                while (!droplet[x].size() > y) { droplet.push_back({}); }
                while (!droplet[x][y].size() > z) { droplet.push_back({}); }
                droplet[x + 1][y + 1][z + 1] = State::POPULATED;
            }

            return droplet;
        }

        bool IsInternalPocket(std::vector<std::vector<std::vector<State>>>& droplet, std::unordered_map<int, bool>& checkedPockets, int x, int y, int z) {
            if (checkedPockets.contains(x * 10000 + y * 100 + z)) { return checkedPockets[x * 10000 + y * 100 + z]; }

            std::queue<std::tuple<int, int, int>> toCheck = { };
            toCheck.push({ x, y, z });
            if (x == 3 && y == 3 && z == 6) {
                int t = 1;
            }
            std::set<int> checked = {};
            while (!toCheck.empty()) {
                auto [px, py, pz] = toCheck.front(); toCheck.pop();
                if (px < 0 || px >= droplet.size() || py < 0 || py >= droplet[px].size() || pz < 0 || pz >= droplet[px][py].size()) {
                    for (auto& checkedCell : checked) {
                        checkedPockets[checkedCell] = false;
                    }
                    return false;
                }
                if (droplet[px][py][pz] != State::EMPTY) { continue; }
                if (checked.contains(px * 10000 + py * 100 + pz)) { continue; }
                checked.insert(px * 10000 + py * 100 + pz);
                for (auto& neighour : neighbours) {
                    auto& [dx, dy, dz] = neighour;
                    toCheck.push({ px + dx, py + dy, pz + dz });
                }
            }
            for (auto& checkedCell : checked) {
                checkedPockets[checkedCell] = true;
            }
            return true;
        }

        int Run(const std::vector<std::string>& input, bool ignorePockets) {
            auto droplet = PreProcessInput(input);

            int surfaceArea = 0;
            std::queue<std::tuple<int, int, int>> toCheck = {};
            for (int x = 0; x < 25; x++) {
                for (int y = 0; y < 25; y++) {
                    for (int z = 0; z < 25; z++) {
                        if (droplet[x][y][z] == State::POPULATED) {
                            toCheck.push({ x, y, z });
                        }
                    }
                }
            }

            std::unordered_map<int, bool> checkedPockets = {};
            while (!toCheck.empty()) {
                auto& [x, y, z] = toCheck.front(); toCheck.pop();
                for (auto& neighour : neighbours) {
                    auto& [dx, dy, dz] = neighour;
                    if (droplet[x + dx][y + dy][z + dz] == State::EMPTY && (ignorePockets || !IsInternalPocket(droplet, checkedPockets, x + dx, y + dy, z + dz))) {
                        surfaceArea++;
                    }
                }
            }

            return surfaceArea;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int surfaceArea = Run(input, true);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { surfaceArea, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int surfaceArea = Run(input, false);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { surfaceArea, endtime - starttime };
        }
    }
}