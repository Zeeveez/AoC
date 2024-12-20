#include "Day16.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day16::Load() {
        input = AoC::Helpers::ReadLines("./Day16.txt");
    }

    void Day16::Parse() {
        // No parsing required
    }

    void Day16::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto [bestScore, _] = Run();

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { bestScore, endTime - startTime };
    }

    void Day16::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        auto [_, tilesOnBests] = Run();

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { tilesOnBests, endTime - startTime };
    }

    std::pair<uint64_t, uint64_t> Day16::Run() {
        int size = input.size();
        std::vector<int> seen(size * size, false);
        std::vector<uint64_t> scoresToTiles(size * size * 4, std::numeric_limits<uint64_t>::max());

        uint64_t bestScore = std::numeric_limits<uint64_t>::max();
        std::vector<uint64_t> tilePathScores(size * size, std::numeric_limits<uint64_t>::max());
        BestPath(
            size,           // map size
            1, size - 2,    // start y == bottom left inside wall
            1, 0,           // start facing east
            seen,
            scoresToTiles,
            0,
            bestScore,
            tilePathScores
        );

        int tilesOnBests = std::count(tilePathScores.begin(), tilePathScores.end(), bestScore) + 1; // include end

        return { bestScore, tilesOnBests };
    }

    void Day16::BestPath(int size, int x, int y, int dx, int dy, std::vector<int>& seen, std::vector<uint64_t>& scoresToTiles, uint64_t score, uint64_t& bestScore, std::vector<uint64_t>& tilePathScores) {
        int tileIdx = y * size + x;
        if (seen[tileIdx]) { return; }

        int dirIdx = (dx > 0) * 2 + (dy > 0);
        if (score > scoresToTiles[tileIdx * 4 + dirIdx]) { return; }
        scoresToTiles[tileIdx * 4 + dirIdx] = score;

        if (x == size - 2 && y == 1) {  // Destination == top right inside wall
            bestScore = score;
            for (size_t i = 0; i < seen.size(); i++) {
                if (seen[i]) {
                    tilePathScores[i] = bestScore;
                }
            }
            return;
        }

        int skippedTileIdx = tileIdx - dy * size - dx;
        seen[tileIdx] = true;
        seen[skippedTileIdx] = true;
        for (int ndx = -1; ndx < 2; ndx += 2) {
            if (ndx == -dx) { continue; }   // No backtracking
            if (input[y][x + ndx] == '#') { continue; }
            // 2's for actual movement and scoring because walls have thickness
            if (score + (std::abs(dy) * 1000 + 2) > bestScore) { continue; }
            BestPath(size, x + ndx * 2, y, ndx, 0, seen, scoresToTiles, score + (std::abs(dy) * 1000 + 2), bestScore, tilePathScores);
        }
        for (int ndy = -1; ndy < 2; ndy += 2) {
            if (ndy == -dy) { continue; }   // No backtracking
            if (input[y + ndy][x] == '#') { continue; }
            // 2's for actual movement and scoring because walls have thickness
            if (score + (std::abs(dx) * 1000 + 2) > bestScore) { continue; }
            BestPath(size, x, y + ndy * 2, 0, ndy, seen, scoresToTiles, score + (std::abs(dx) * 1000 + 2), bestScore, tilePathScores);
        }
        seen[skippedTileIdx] = false;
        seen[tileIdx] = false;
    }
}