#pragma once
#include <cstdint>
#include <optional>
#include <vector>
#include <string>

#include "../Day/Day.h"

namespace AoC2024 {
    class Day11 : public AoC::Day {
    private:
        class Stone {
        public:
            uint64_t value;
            uint64_t count;
            Stone() = default;
            Stone(uint64_t value, uint64_t count);
            std::optional<Stone> Iterate();
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day11() : Day() {
            dayNo = 11;
            Load();
            Parse();
            A();
            B();
        }

    private:
        std::vector<uint64_t> input = {};

        uint64_t Run(int iterations);
    };
}