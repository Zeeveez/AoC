#pragma once
#include <vector>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day08 : public AoC::Day<std::vector<std::string>, 2025, 8> {
    private:
        struct Vec3 {
        public:
            std::int64_t x;
            std::int64_t y;
            std::int64_t z;
            int network = -1;
            std::int64_t Dist(Vec3& other) {
                return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
            }
        };

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<Vec3> sockets;

        std::vector<std::tuple<std::uint64_t, std::size_t, std::size_t>> GetSocketDistances();
        void AddToNetworks(std::unordered_map<int, std::vector<Vec3*>>& networks, std::size_t idx1, std::size_t idx2);
    };
}