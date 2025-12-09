#include "Day07.h"

namespace AoC2025 {
    void Day07::Parse() {
        splitters = {};

        for (int x = 0; x < rawData[0].size(); x++) {
            if (rawData[0][x] == 'S') { beamStart = x; break; }
        }
        for (int i = 2; i < rawData.size(); i += 2) {
            splitters.push_back({});
            for (int x = 0; x < rawData[i].length(); x++) {
                if (rawData[i][x] == '^') { splitters.back().insert(x); }
            }
        }
    }

    AoC::DayResult::PuzzleResult Day07::A() {
        std::uint64_t res = 0;

        std::unordered_set<int> beams = { beamStart };
        for (auto& splitterSet : splitters) {
            std::unordered_set<int> newBeams = {};
            for (auto& beam : beams) {
                if (splitterSet.contains(beam)) {
                    res++;
                    newBeams.insert(beam - 1);
                    newBeams.insert(beam + 1);
                }
                else {
                    newBeams.insert(beam);
                }
            }
            beams = newBeams;
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day07::B() {
        std::uint64_t res = 0;

        std::unordered_map<int, std::size_t> beamCounts = { { beamStart, 1 } };
        for (auto& splitterSet : splitters) {
            std::unordered_map<int, std::size_t> newBeamCounts = {};
            for (auto& beam : beamCounts) {
                if (splitterSet.contains(beam.first)) {
                    newBeamCounts[beam.first - 1] += beam.second;
                    newBeamCounts[beam.first + 1] += beam.second;
                }
                else {
                    newBeamCounts[beam.first] += beam.second;
                }
            }
            beamCounts = newBeamCounts;
        }
        for (auto& beamCount : beamCounts) {
            res += beamCount.second;
        }

        return res;
    }
}