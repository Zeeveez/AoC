#pragma once

#include <variant>
#include <cstdint>
#include <chrono>
#include <ostream>

namespace AoC {
    class Day {
    public:
        typedef std::variant<std::string, uint64_t> PuzzleResult;
        typedef std::pair<PuzzleResult, std::chrono::duration<double, std::milli>> PartResult;

        int dayNo;
        PartResult partAResult;
        PartResult partBResult;

        Day(int dayNo);
        virtual void Load() = 0;
        virtual void Parse() = 0;
        virtual void A() = 0;
        virtual void B() = 0;

        friend std::ostream& operator<<(std::ostream& stream, const Day& partResult);
    };
}
