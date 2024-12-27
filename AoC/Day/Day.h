#pragma once
#include <variant>
#include <cstdint>
#include <chrono>
#include <ostream>
#include <functional>

namespace AoC {
    class Day {
    public:
        typedef std::variant<std::string, uint64_t, int64_t, uint32_t, uint16_t> PuzzleResult;
        typedef std::pair<PuzzleResult, std::chrono::duration<double, std::milli>> PartResult;

        int dayNo = -1;
        PartResult parseResult = { "TODO" , {std::chrono::duration<double, std::milli>(0) } };
        PartResult partAResult = { "TODO" , {std::chrono::duration<double, std::milli>(0) } };
        PartResult partBResult = { "TODO" , {std::chrono::duration<double, std::milli>(0) } };

        Day();
        virtual void Load() {};
        virtual void Parse() {};
        virtual void A() {};
        virtual void B() {};

        std::chrono::duration<double, std::milli> TimeFunc(std::function<void()> f);

        friend std::ostream& operator<<(std::ostream& stream, const Day& day);
    };
}
