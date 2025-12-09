#include <cmath>

#include "Day09.h"

namespace AoC2025 {
    void Day09::Parse() {
        points = {};

        for (auto& line : rawData) {
            std::int64_t v = 0;
            for (auto& c : line) {
                if (std::isdigit(c)) { v = v * 10 + c - '0'; }
                else if (c == ',') {
                    points.push_back({ v, 0 });
                    v = 0;
                }
            }
            points.back().second = v;
        }
    }

    AoC::DayResult::PuzzleResult Day09::A() {
        std::int64_t res = 0;

        for (int i = 0; i < points.size(); i++) {
            for (int j = i; j < points.size(); j++) {
                auto q1 = points[i];
                auto q2 = points[j];

                auto width = (std::llabs(q1.first - q2.first) + 1);
                auto height = (std::llabs(q1.second - q2.second) + 1);
                res = std::max(width * height, res);
            }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day09::B() {
        std::int64_t res = 0;

        for (int i = 0; i < points.size(); i++) {
            for (int j = i; j < points.size(); j++) {
                auto q1 = points[i];
                auto q2 = points[j];

                bool good = true;
                for (int k = 0; k < points.size(); k++) {
                    auto p1 = points[k];
                    auto p2 = points[(k + 1) % points.size()];

                    if (PointInsideRect(q1, q2, p1)) { good = false; break; }
                    if (PointInsideRect(q1, q2, p2)) { good = false; break; }
                    if (LineIntersectsRect(q1, q2, p1, p2)) { good = false; break; }
                }

                if (good) {
                    auto width = (std::llabs(q1.first - q2.first) + 1);
                    auto height = (std::llabs(q1.second - q2.second) + 1);
                    res = std::max(width * height, res);
                }
            }
        }
        return res;
    }

    bool Day09::PointInsideRect(std::pair<std::int64_t, std::int64_t> rectP1, std::pair<std::int64_t, std::int64_t> rectP2, std::pair<std::int64_t, std::int64_t> testPoint) {
        if (testPoint.first <= std::min(rectP1.first, rectP2.first)) { return false; }
        if (testPoint.first >= std::max(rectP1.first, rectP2.first)) { return false; }
        if (testPoint.second <= std::min(rectP1.second, rectP2.second)) { return false; }
        if (testPoint.second >= std::max(rectP1.second, rectP2.second)) { return false; }
        return true;
    }

    bool Day09::LineIntersectsRect(std::pair<std::int64_t, std::int64_t> rectP1, std::pair<std::int64_t, std::int64_t> rectP2, std::pair<std::int64_t, std::int64_t> lineP1, std::pair<std::int64_t, std::int64_t> lineP2) {
        auto left = std::min(rectP1.first, rectP2.first);
        auto right = std::max(rectP1.first, rectP2.first);
        auto top = std::max(rectP1.second, rectP2.second);
        auto bottom = std::min(rectP1.second, rectP2.second);

        if (lineP1.first == lineP2.first) {
            // Vertical line
            if (lineP1.first <= left || lineP1.first >= right) { return false; }

            auto lineTop = std::max(lineP1.second, lineP2.second);
            auto lineBottom = std::min(lineP1.second, lineP2.second);
            if (lineTop > top && lineBottom < top) { return true; }
            if (lineTop > bottom && lineBottom < bottom) { return true; }
        }
        else {
            // Horizontal line
            if (lineP1.second <= bottom || lineP1.second >= top) { return false; }

            auto lineLeft = std::min(lineP1.first, lineP2.first);
            auto lineRight = std::max(lineP1.first, lineP2.first);
            if (lineLeft < left && lineRight > left) { return true; }
            if (lineLeft < right && lineRight > right) { return true; }
        }
        return false;
    }
}