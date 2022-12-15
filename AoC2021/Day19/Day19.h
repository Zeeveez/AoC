#ifndef DAY19_H
#define DAY19_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day19 {
        const std::vector<std::vector<std::pair<int, int>>> transformations = {
            // Positive X -> positive X
            { {  1, 0 }, {  1, 1 }, {  1, 2 } },
            { {  1, 0 }, {  1, 2 }, { -1, 1 } },
            { {  1, 0 }, { -1, 1 }, { -1, 2 } },
            { {  1, 0 }, { -1, 2 }, {  1, 1 } },

            // Positive X -> negative X
            { { -1, 0 }, {  1, 1 }, { -1, 2 } },
            { { -1, 0 }, { -1, 2 }, { -1, 1 } },
            { { -1, 0 }, { -1, 1 }, {  1, 2 } },
            { { -1, 0 }, {  1, 2 }, {  1, 1 } },

            // Positive X -> positive Y
            { {  1, 1 }, { -1, 0 }, {  1, 2 } },
            { {  1, 1 }, { -1, 2 }, { -1, 0 } },
            { {  1, 1 }, {  1, 0 }, { -1, 2 } },
            { {  1, 1 }, {  1, 2 }, {  1, 0 } },

            // Positive X -> negative y
            { { -1, 1 }, {  1, 0 }, {  1, 2 } },
            { { -1, 1 }, {  1, 2 }, { -1, 0 } },
            { { -1, 1 }, { -1, 0 }, { -1, 2 } },
            { { -1, 1 }, { -1, 2 }, {  1, 0 } },

            // Positive X -> positive Z
            { {  1, 2 }, {  1, 1 }, { -1, 0 } },
            { {  1, 2 }, { -1, 0 }, { -1, 1 } },
            { {  1, 2 }, { -1, 1 }, {  1, 0 } },
            { {  1, 2 }, {  1, 0 }, {  1, 1 } },

            // Positive X -> negative Z
            { { -1, 2 }, {  1, 1 }, {  1, 0 } },
            { { -1, 2 }, {  1, 0 }, { -1, 1 } },
            { { -1, 2 }, { -1, 1 }, { -1, 0 } },
            { { -1, 2 }, { -1, 0 }, {  1, 1 } },

            //// XYZ
            //{ {  1, 0 }, {  1, 1 }, {  1, 2 } },    // No Reverse
            //{ { -1, 0 }, {  1, 1 }, {  1, 2 } },    // Reverse X
            //{ {  1, 0 }, { -1, 1 }, {  1, 2 } },    // Reverse Y
            //{ {  1, 0 }, {  1, 1 }, { -1, 2 } },    // Reverse Z
            //{ { -1, 0 }, { -1, 1 }, {  1, 2 } },    // Reverse XY
            //{ { -1, 0 }, {  1, 1 }, { -1, 2 } },    // Reverse XZ
            //{ {  1, 0 }, { -1, 1 }, { -1, 2 } },    // Reverse YZ
            //{ { -1, 0 }, { -1, 1 }, { -1, 2 } },    // Reverse XYZ

            //// YXZ
            //{ {  1, 1 }, {  1, 0 }, {  1, 2 } },    // No Reverse
            //{ { -1, 1 }, {  1, 0 }, {  1, 2 } },    // Reverse X
            //{ {  1, 1 }, { -1, 0 }, {  1, 2 } },    // Reverse Y
            //{ {  1, 1 }, {  1, 0 }, { -1, 2 } },    // Reverse Z
            //{ { -1, 1 }, { -1, 0 }, {  1, 2 } },    // Reverse XY
            //{ { -1, 1 }, {  1, 0 }, { -1, 2 } },    // Reverse XZ
            //{ {  1, 1 }, { -1, 0 }, { -1, 2 } },    // Reverse YZ
            //{ { -1, 1 }, { -1, 0 }, { -1, 2 } },    // Reverse XYZ

            //// ZYX
            //{ {  1, 2 }, {  1, 1 }, {  1, 0 } },    // No Reverse
            //{ { -1, 2 }, {  1, 1 }, {  1, 0 } },    // Reverse X
            //{ {  1, 2 }, { -1, 1 }, {  1, 0 } },    // Reverse Y
            //{ {  1, 2 }, {  1, 1 }, { -1, 0 } },    // Reverse Z
            //{ { -1, 2 }, { -1, 1 }, {  1, 0 } },    // Reverse XY
            //{ { -1, 2 }, {  1, 1 }, { -1, 0 } },    // Reverse XZ
            //{ {  1, 2 }, { -1, 1 }, { -1, 0 } },    // Reverse YZ
            //{ { -1, 2 }, { -1, 1 }, { -1, 0 } },    // Reverse XYZ

            //// XZY
            //{ {  1, 0 }, {  1, 2 }, {  1, 1 } },    // No Reverse
            //{ { -1, 0 }, {  1, 2 }, {  1, 1 } },    // Reverse X
            //{ {  1, 0 }, { -1, 2 }, {  1, 1 } },    // Reverse Y
            //{ {  1, 0 }, {  1, 2 }, { -1, 1 } },    // Reverse Z
            //{ { -1, 0 }, { -1, 2 }, {  1, 1 } },    // Reverse XY
            //{ { -1, 0 }, {  1, 2 }, { -1, 1 } },    // Reverse XZ
            //{ {  1, 0 }, { -1, 2 }, { -1, 1 } },    // Reverse YZ
            //{ { -1, 0 }, { -1, 2 }, { -1, 1 } },    // Reverse XYZ

            //// YZX
            //{ {  1, 1 }, {  1, 2 }, {  1, 0 } },    // No Reverse
            //{ { -1, 1 }, {  1, 2 }, {  1, 0 } },    // Reverse X
            //{ {  1, 1 }, { -1, 2 }, {  1, 0 } },    // Reverse Y
            //{ {  1, 1 }, {  1, 2 }, { -1, 0 } },    // Reverse Z
            //{ { -1, 1 }, { -1, 2 }, {  1, 0 } },    // Reverse XY
            //{ { -1, 1 }, {  1, 2 }, { -1, 0 } },    // Reverse XZ
            //{ {  1, 1 }, { -1, 2 }, { -1, 0 } },    // Reverse YZ
            //{ { -1, 1 }, { -1, 2 }, { -1, 0 } },    // Reverse XYZ

            //// ZXY
            //{ {  1, 2 }, {  1, 0 }, {  1, 1 } },    // No Reverse
            //{ { -1, 2 }, {  1, 0 }, {  1, 1 } },    // Reverse X
            //{ {  1, 2 }, { -1, 0 }, {  1, 1 } },    // Reverse Y
            //{ {  1, 2 }, {  1, 0 }, { -1, 1 } },    // Reverse Z
            //{ { -1, 2 }, { -1, 0 }, {  1, 1 } },    // Reverse XY
            //{ { -1, 2 }, {  1, 0 }, { -1, 1 } },    // Reverse XZ
            //{ {  1, 2 }, { -1, 0 }, { -1, 1 } },    // Reverse YZ
            //{ { -1, 2 }, { -1, 0 }, { -1, 1 } },    // Reverse XYZ
        };

        std::vector<std::vector<std::vector<int>>> PreProcessInput(const std::vector<std::string>& input);

        std::vector<int> Transform(const std::vector<int>& input, int transformation);
        std::vector<std::vector<int>> Transform(const std::vector<std::vector<int>>& input, int transformation);

        bool AddToMap(std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& scanners, const std::vector<std::vector<int>>& beacons, int transformation);
        bool AddToMap(std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& scanners, const std::vector<std::vector<int>>& beacons);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif