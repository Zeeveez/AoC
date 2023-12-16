#include "Day16.h"

#include <iostream>
#include <numeric>
#include <queue>
#include <set>

namespace AoC2023::Day16 {
    size_t Run(const std::vector<std::string>& grid, std::pair<std::pair<int, int>, std::pair<int, int>> startBeam) {
        std::queue<std::pair<std::pair<int, int>, std::pair<int, int>>> beams = {};
        beams.push(startBeam);

        std::set<std::pair<int, int>> visited = {};
        std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> seen = {};

        while (beams.size()) {
            auto& beam = beams.front(); beams.pop();
            if (seen.contains(beam)) { continue; }
            seen.insert(beam);

            auto& [beamPos, beamDir] = beam;

            if (beamPos.second < 0 || beamPos.second >= grid.size()) { continue; }
            if (beamPos.first < 0 || beamPos.first >= grid[beamPos.second].length()) { continue; }

            visited.insert(beamPos);

            // Empty space
            if (grid[beamPos.second][beamPos.first] == '.') {
                beams.push({ {beamPos.first + beamDir.first, beamPos.second + beamDir.second}, beamDir });
            }

            // Pointy end of a splitter
            else if (grid[beamPos.second][beamPos.first] == '-' && std::abs(beamDir.first) == 1) {
                beams.push({ {beamPos.first + beamDir.first, beamPos.second + beamDir.second}, beamDir });
            }
            else if (grid[beamPos.second][beamPos.first] == '|' && std::abs(beamDir.second) == 1) {
                beams.push({ {beamPos.first + beamDir.first, beamPos.second + beamDir.second}, beamDir });
            }

            // Flat end of a splitter
            else if (grid[beamPos.second][beamPos.first] == '|' && std::abs(beamDir.first) == 1) {
                beams.push({ {beamPos.first, beamPos.second - 1}, { 0, -1 } });
                beams.push({ {beamPos.first, beamPos.second + 1}, { 0, 1 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '-' && std::abs(beamDir.second) == 1) {
                beams.push({ {beamPos.first - 1, beamPos.second }, { -1, 0 } });
                beams.push({ {beamPos.first + 1, beamPos.second }, { 1, 0 } });
            }

            // Mirror
            else if (grid[beamPos.second][beamPos.first] == '\\' && beamDir.first == 1) {
                beams.push({ {beamPos.first, beamPos.second + 1}, { 0, 1 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '/' && beamDir.first == 1) {
                beams.push({ {beamPos.first, beamPos.second - 1}, { 0, -1 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '\\' && beamDir.first == -1) {
                beams.push({ {beamPos.first, beamPos.second - 1}, { 0, -1 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '/' && beamDir.first == -1) {
                beams.push({ {beamPos.first, beamPos.second + 1}, { 0, 1 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '\\' && beamDir.second == 1) {
                beams.push({ {beamPos.first + 1, beamPos.second}, { 1, 0 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '/' && beamDir.second == 1) {
                beams.push({ {beamPos.first - 1, beamPos.second}, { -1, 0 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '\\' && beamDir.second == -1) {
                beams.push({ {beamPos.first - 1, beamPos.second}, { -1, 0 } });
            }
            else if (grid[beamPos.second][beamPos.first] == '/' && beamDir.second == -1) {
                beams.push({ {beamPos.first + 1, beamPos.second}, { 1, 0 } });
            }



            else {
                // Unhandled situation
                throw;
            }

        }

        return visited.size();
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = Run(input, { { 0, 0 }, { 1, 0 } });

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = 0;
        for (size_t i = 0; i < input.size(); i++) {
            score = std::max(score, Run(input, { { 0, i }, { 1, 0 } }));
            score = std::max(score, Run(input, { { input[0].size() - 1, i}, {-1, 0}}));
        }
        for (size_t i = 0; i < input[0].size(); i++) {
            score = std::max(score, Run(input, { { i, 0 }, { 0, 1 } }));
            score = std::max(score, Run(input, { { i, input.size() - 1 }, { 0, -1 } }));
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}