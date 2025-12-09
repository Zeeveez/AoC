#include <numeric>
#include <queue>
#include <set>

#include "Day16.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day16::Load() {
        input = AoC::Helpers::ReadLines("./Day16.txt");
    }

    void Day16::Parse() {
        // No parsing required
    }

    void Day16::A() {
        partAResult.first = Run({ { 0, 0 }, { 1, 0 } });
    }

    void Day16::B() {
        uint64_t res = 0;
        for (size_t i = 0; i < input.size(); i++) {
            res = std::max(res, Run({ { 0, i }, { 1, 0 } }));
            res = std::max(res, Run({ { input[0].size() - 1, i}, {-1, 0} }));
        }
        for (size_t i = 0; i < input[0].size(); i++) {
            res = std::max(res, Run({ { i, 0 }, { 0, 1 } }));
            res = std::max(res, Run({ { i, input.size() - 1 }, { 0, -1 } }));
        }
        partBResult.first = res;
    }

    size_t Day16::Run(std::pair<std::pair<int, int>, std::pair<int, int>> startBeam) {
        std::queue<std::pair<std::pair<int, int>, std::pair<int, int>>> beams = {};
        beams.push(startBeam);

        std::set<std::pair<int, int>> visited = {};
        std::set<std::pair<std::pair<int, int>, std::pair<int, int>>> seen = {};

        while (beams.size()) {
            auto& beam = beams.front(); beams.pop();
            if (seen.contains(beam)) { continue; }
            seen.insert(beam);

            auto& [beamPos, beamDir] = beam;

            if (beamPos.second < 0 || beamPos.second >= input.size()) { continue; }
            if (beamPos.first < 0 || beamPos.first >= input[beamPos.second].length()) { continue; }

            visited.insert(beamPos);

            // Empty space
            if (input[beamPos.second][beamPos.first] == '.') {
                beams.push({ {beamPos.first + beamDir.first, beamPos.second + beamDir.second}, beamDir });
            }

            // Pointy end of a splitter
            else if (input[beamPos.second][beamPos.first] == '-' && std::abs(beamDir.first) == 1) {
                beams.push({ {beamPos.first + beamDir.first, beamPos.second + beamDir.second}, beamDir });
            }
            else if (input[beamPos.second][beamPos.first] == '|' && std::abs(beamDir.second) == 1) {
                beams.push({ {beamPos.first + beamDir.first, beamPos.second + beamDir.second}, beamDir });
            }

            // Flat end of a splitter
            else if (input[beamPos.second][beamPos.first] == '|' && std::abs(beamDir.first) == 1) {
                beams.push({ {beamPos.first, beamPos.second - 1}, { 0, -1 } });
                beams.push({ {beamPos.first, beamPos.second + 1}, { 0, 1 } });
            }
            else if (input[beamPos.second][beamPos.first] == '-' && std::abs(beamDir.second) == 1) {
                beams.push({ {beamPos.first - 1, beamPos.second }, { -1, 0 } });
                beams.push({ {beamPos.first + 1, beamPos.second }, { 1, 0 } });
            }

            // Mirror
            else if (input[beamPos.second][beamPos.first] == '\\' && beamDir.first == 1) {
                beams.push({ {beamPos.first, beamPos.second + 1}, { 0, 1 } });
            }
            else if (input[beamPos.second][beamPos.first] == '/' && beamDir.first == 1) {
                beams.push({ {beamPos.first, beamPos.second - 1}, { 0, -1 } });
            }
            else if (input[beamPos.second][beamPos.first] == '\\' && beamDir.first == -1) {
                beams.push({ {beamPos.first, beamPos.second - 1}, { 0, -1 } });
            }
            else if (input[beamPos.second][beamPos.first] == '/' && beamDir.first == -1) {
                beams.push({ {beamPos.first, beamPos.second + 1}, { 0, 1 } });
            }
            else if (input[beamPos.second][beamPos.first] == '\\' && beamDir.second == 1) {
                beams.push({ {beamPos.first + 1, beamPos.second}, { 1, 0 } });
            }
            else if (input[beamPos.second][beamPos.first] == '/' && beamDir.second == 1) {
                beams.push({ {beamPos.first - 1, beamPos.second}, { -1, 0 } });
            }
            else if (input[beamPos.second][beamPos.first] == '\\' && beamDir.second == -1) {
                beams.push({ {beamPos.first - 1, beamPos.second}, { -1, 0 } });
            }
            else if (input[beamPos.second][beamPos.first] == '/' && beamDir.second == -1) {
                beams.push({ {beamPos.first + 1, beamPos.second}, { 1, 0 } });
            }



            else {
                // Unhandled situation
                throw;
            }

        }

        return visited.size();
    }
}