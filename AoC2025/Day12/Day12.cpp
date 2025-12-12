#include "Day12.h"

namespace AoC2025 {
    void Day12::Parse() {
        baseShapes = {};
        boxes = {};
        for (auto& line : rawData) {
            if (line == "") { continue; }
            else if (line.back() == ':') {
                baseShapes.push_back({});
                baseShapeBits.push_back({});
            }
            else if (line[0] == '.' || line[0] == '#') {
                baseShapes.back().push_back({});
                for (auto& c : line) {
                    baseShapes.back().back().push_back(c == '#');
                    baseShapeBits.back() += c == '#';
                }
            }
            else {
                boxes.push_back({ { 0, 0 }, {} });
                int v = 0;
                for (auto& c : line) {
                    if (c >= '0' && c <= '9') { v = v * 10 + c - '0'; }
                    else if (v == 0) { continue; }
                    else if (boxes.back().first.first == 0) { boxes.back().first.first = v; v = 0; }
                    else if (boxes.back().first.second == 0) { boxes.back().first.second = v; v = 0; }
                    else { boxes.back().second.push_back(v); v = 0; }
                }
                boxes.back().second.push_back(v);
            }
        }
    }

    AoC::DayResult::PuzzleResult Day12::A() {
        std::uint64_t res = 0;
        for (auto& box : boxes) {
            std::uint64_t boxTotalBits = 0;
            for (int i = 0; i < box.second.size(); i++) {
                boxTotalBits += box.second[i] * baseShapeBits[i];
            }
            if (boxTotalBits <= box.first.first * box.first.second) {
                res += 1;
            }
        }
        return res;
    }

    AoC::DayResult::PuzzleResult Day12::B() {
        return "Merry Christmas!";
    }
}