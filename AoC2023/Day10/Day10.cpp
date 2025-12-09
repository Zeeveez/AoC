#include <queue>

#include "Day10.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day10::Load() {
        input = AoC::Helpers::ReadLines("./Day10.txt");
    }

    void Day10::Parse() {
        for (auto& line : input) {
            std::vector<Pipe> row = {};
            for (auto& c : line) {
                switch (c) {
                case '|':
                    row.push_back(Pipe::UP_DOWN);
                    break;
                case '-':
                    row.push_back(Pipe::LEFT_RIGHT);
                    break;
                case 'L':
                    row.push_back(Pipe::UP_RIGHT);
                    break;
                case 'J':
                    row.push_back(Pipe::UP_LEFT);
                    break;
                case '7':
                    row.push_back(Pipe::DOWN_LEFT);
                    break;
                case 'F':
                    row.push_back(Pipe::DOWN_RIGHT);
                    break;
                case '.':
                    row.push_back(Pipe::GROUND);
                    break;
                case 'S':
                    row.push_back(Pipe::START);
                    break;
                }
            }
            grid.push_back(row);
        }
        // No parsing required
    }

    void Day10::A() {
        auto start = FindStart();
        auto path = FindPath(start);
        auto res = path.size() / 2;   // Furthest difference through a loop is half its size
        partAResult.first = res;
    }

    void Day10::B() {
        partBResult.first = InflateAndFillGrid();
    }

    size_t Day10::InflateAndFillGrid() {
        std::vector<std::vector<int>> output = {};
        output.push_back({ 0,0,0,0,0,0 });
        output.push_back({ 0,0,0,0,0,0 });
        output.push_back({ 0,0,0,0,0,0 });
        for (size_t x = 0; x < grid[0].size(); x++) {
            output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
            output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0);
            output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
        }
        for (size_t y = 0; y < grid.size(); y++) {
            output.push_back({});
            output.push_back({});
            output.push_back({});
            output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
            output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0);
            output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
            for (size_t x = 0; x < grid[y].size(); x++) {
                switch (grid[y][x]) {
                case Pipe::UP_DOWN:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(1); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(0);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(1); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::LEFT_RIGHT:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::UP_RIGHT:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(1); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::UP_LEFT:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(1); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(0);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::DOWN_LEFT:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(0);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(1); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::DOWN_RIGHT:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(1); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::GROUND:
                    output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
                    output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0);
                    output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
                    break;
                case Pipe::START:
                    output[output.size() - 3].push_back(1); output[output.size() - 3].push_back(1); output[output.size() - 3].push_back(1);
                    output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1); output[output.size() - 2].push_back(1);
                    output[output.size() - 1].push_back(1); output[output.size() - 1].push_back(1); output[output.size() - 1].push_back(1);
                    break;
                }
            }
            output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
            output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0);
            output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
        }
        output.push_back({ 0,0,0,0,0,0 });
        output.push_back({ 0,0,0,0,0,0 });
        output.push_back({ 0,0,0,0,0,0 });
        for (size_t x = 0; x < grid[0].size(); x++) {
            output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0); output[output.size() - 1].push_back(0);
            output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0); output[output.size() - 2].push_back(0);
            output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0); output[output.size() - 3].push_back(0);
        }

        std::set<std::pair<size_t, size_t>> visited = {};
        std::queue<std::pair<size_t, size_t>> queue = {};

        std::pair<size_t, size_t> pos = { 1, 1 };
        visited.insert(pos);
        queue.push(pos);

        while (queue.size()) {
            auto currentPos = queue.front(); queue.pop();

            for (auto& neighbour : GetAllNeighbours(output, currentPos)) {
                if (output[neighbour.second][neighbour.first] == 0 && !visited.contains(neighbour)) {
                    output[neighbour.second][neighbour.first] = 1;
                    visited.insert(neighbour);
                    queue.push(neighbour);
                }
            }
        }

        size_t result = 0;
        for (size_t y = 4; y < output.size() - 3; y += 3) {
            for (size_t x = 4; x < output[y].size() - 3; x += 3) {
                size_t c = 0;
                for (int dx = -1; dx < 2; dx++) {
                    for (int dy = -1; dy < 2; dy++) {
                        c += output[(int)y + dy][(int)x + dx];
                    }
                }
                if (c == 3 || c == 0) {
                    result++;
                }
            }
        }
        return result;
    }

    std::pair<size_t, size_t> Day10::FindStart() {
        for (size_t y = 0; y < grid.size(); y++) {
            for (size_t x = 0; x < grid[y].size(); x++) {
                if (grid[y][x] == Pipe::START) {
                    return { x, y };
                }
            }
        }
        return { 0, 0 };
    }

    std::vector<std::pair<size_t, size_t>> Day10::GetPathNeighbours(const std::pair<size_t, size_t>& pos) {
        std::vector<std::pair<size_t, size_t>> neighbours = {};
        auto pipe = grid[pos.second][pos.first];

        if (pipe == Pipe::START) {
            auto up = pos.second > 0 ? grid[pos.second - 1][pos.first] : Pipe::GROUND;
            auto down = pos.second < grid.size() - 1 ? grid[pos.second + 1][pos.first] : Pipe::GROUND;
            auto left = pos.first > 0 ? grid[pos.second][pos.first - 1] : Pipe::GROUND;
            auto right = pos.first < grid[pos.second].size() - 1 ? grid[pos.second][pos.first + 1] : Pipe::GROUND;

            if ((up == Pipe::UP_DOWN || up == Pipe::DOWN_LEFT || up == Pipe::DOWN_RIGHT) && pos.second < grid.size() - 1) { neighbours.push_back({ pos.first, pos.second - 1 }); }
            if ((down == Pipe::UP_DOWN || down == Pipe::UP_RIGHT || down == Pipe::UP_LEFT) && pos.second > 0) { neighbours.push_back({ pos.first, pos.second + 1 }); }
            if ((left == Pipe::LEFT_RIGHT || left == Pipe::UP_RIGHT || left == Pipe::DOWN_RIGHT) && pos.first < grid[pos.second].size() - 1) { neighbours.push_back({ pos.first - 1, pos.second }); }
            if ((right == Pipe::LEFT_RIGHT || right == Pipe::UP_LEFT || right == Pipe::DOWN_LEFT) && pos.first > 0) { neighbours.push_back({ pos.first + 1, pos.second }); }
        }

        else {
            if ((pipe == Pipe::UP_DOWN || pipe == Pipe::UP_RIGHT || pipe == Pipe::UP_LEFT) && pos.second > 0) { neighbours.push_back({ pos.first, pos.second - 1 }); }
            if ((pipe == Pipe::UP_DOWN || pipe == Pipe::DOWN_LEFT || pipe == Pipe::DOWN_RIGHT) && pos.second < grid.size() - 1) { neighbours.push_back({ pos.first, pos.second + 1 }); }
            if ((pipe == Pipe::LEFT_RIGHT || pipe == Pipe::UP_LEFT || pipe == Pipe::DOWN_LEFT) && pos.first > 0) { neighbours.push_back({ pos.first - 1, pos.second }); }
            if ((pipe == Pipe::LEFT_RIGHT || pipe == Pipe::UP_RIGHT || pipe == Pipe::DOWN_RIGHT) && pos.first < grid[pos.second].size() - 1) { neighbours.push_back({ pos.first + 1, pos.second }); }
        }

        return neighbours;
    }

    std::vector<std::pair<size_t, size_t>> Day10::GetAllNeighbours(const std::vector<std::vector<int>>& grid, const std::pair<size_t, size_t>& pos) {
        std::vector<std::pair<size_t, size_t>> neighbours = {};

        for (int dy = -1; dy < 2; dy++) {
            if (dy == -1 && pos.second <= 0) { continue; }
            if (dy == 1 && pos.second >= grid.size() - 1) { continue; }

            for (int dx = -1; dx < 2; dx++) {
                if (dx == 0 && dy == 0) { continue; }
                if (dx == -1 && pos.first <= 0) { continue; }
                if (dx == 1 && pos.first >= grid[pos.second + dy].size() - 1) { continue; }

                neighbours.push_back({ pos.first + dx, pos.second + dy });
            }
        }

        return neighbours;
    }

    std::set<std::pair<size_t, size_t>> Day10::FindPath(const std::pair<size_t, size_t>& pos) {
        std::set<std::pair<size_t, size_t>> visited = {};
        std::queue<std::pair<size_t, size_t>> queue = {};

        visited.insert(pos);
        queue.push(pos);

        uint64_t size = 0;
        while (queue.size()) {
            auto currentPos = queue.front(); queue.pop();
            size++;

            for (auto& neighbour : GetPathNeighbours(currentPos)) {
                if (!visited.contains(neighbour)) {
                    visited.insert(neighbour);
                    queue.push(neighbour);
                }
            }
        }

        return visited;
    }
}