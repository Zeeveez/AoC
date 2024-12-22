#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day14 : public AoC::Day {
    private:
        typedef std::pair<int64_t, int64_t> Position;
        typedef std::pair<int64_t, int64_t> Speed;
        typedef std::pair<Position, Speed> Robot;

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day14() : Day() {
            dayNo = 14;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<Robot> robots = {};
    };
}