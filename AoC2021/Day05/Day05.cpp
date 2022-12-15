#include "Day05.h"

namespace AoC2021 {
    namespace Day05 {
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines = {};

            int i = 0;
            while (i < input.size()) {
                std::string p1 = input[i];
                std::string p2 = input[i + 2];
                lines.push_back({
                    {
                        std::stoi(p1.substr(0, p1.find(','))),
                        std::stoi(p1.substr(p1.find(',') + 1, std::string::npos)),
                    },
                    {
                        std::stoi(p2.substr(0, p2.find(','))),
                        std::stoi(p2.substr(p2.find(',') + 1, std::string::npos)),
                    }
                                });
                i += 3;
            }
            return lines;
        }

        void DrawPoint(std::map<std::pair<int, int>, int>& vents, const std::pair<int, int> p) {
            if (vents.count(p) == 0) {
                vents.insert({ p, 0 });
            }
            vents[p]++;
        }

        void DrawLine(std::map<std::pair<int, int>, int>& vents, const std::pair<int, int>& p1, const std::pair<int, int>& p2, bool drawDiagonals) {
            if (!drawDiagonals && !(p1.first == p2.first || p1.second == p2.second)) { return; }
            if (p1.first > p2.first) { DrawLine(vents, p2, p1, drawDiagonals); return; }
            // p1.x is guaranteed to be <= p2.x

            if (p1.first == p2.first) {
                if (p1.second < p2.second) {
                    for (int y = p1.second; y <= p2.second; y++) {
                        DrawPoint(vents, { p1.first, y });
                    }
                }
                else {
                    for (int y = p2.second; y <= p1.second; y++) {
                        DrawPoint(vents, { p1.first, y });
                    }
                }
            }
            else {
                for (int x = p1.first; x <= p2.first; x++) {
                    if (p1.second < p2.second) {
                        DrawPoint(vents, { x, p1.second + x - p1.first });
                    }
                    else if (p1.second == p2.second) {
                        DrawPoint(vents, { x, p1.second });
                    }
                    else {
                        DrawPoint(vents, { x, p1.second - (x - p1.first) });
                    }
                }
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input, bool drawDiagonals) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto data = PreProcessInput(input);

            std::map<std::pair<int, int>, int> vents = {};
            for (auto& line : data) {
                DrawLine(vents, line.first, line.second, drawDiagonals);
            }

            int c = 0;
            for (auto& kvp : vents) {
                if (kvp.second >= 2) {
                    c++;
                }
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            return A(input, true);
        }
    }
}