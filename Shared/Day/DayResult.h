#pragma once
#include <type_traits>
#include <variant>
#include <cstdint>
#include <chrono>
#include <ostream>

#include "../../Helpers/Helpers.h"

namespace AoC {
    struct DayResult {
    public:
        typedef std::variant<std::string, std::uint64_t, std::int64_t, std::uint32_t, std::uint16_t> PuzzleResult;
        typedef std::pair<PuzzleResult, std::chrono::duration<double, std::milli>> PartResult;

        PartResult ioResult = { "N/A" , {std::chrono::duration<double, std::milli>(0) } };
        PartResult parseResult = { "N/A" , {std::chrono::duration<double, std::milli>(0) } };
        PartResult partAResult = { "TODO" , {std::chrono::duration<double, std::milli>(0) } };
        PartResult partBResult = { "TODO" , {std::chrono::duration<double, std::milli>(0) } };

        int dayNo = 0;
        DayResult(int dayNo) : dayNo(dayNo) {}

        friend std::ostream& operator<<(std::ostream& stream, const DayResult& day)
        {
            stream << "Day " << std::format("{:2}", day.dayNo) << " - A: (" << std::format("{:10.4f}", day.ioResult.second.count()) << "ms + " << std::format("{:10.4f}", day.parseResult.second.count()) << "ms + " << std::format("{:10.4f}", day.partAResult.second.count()) << "ms): ";
            std::visit([&stream](const auto& v) { stream << v; }, day.partAResult.first);
            stream << "\n";

            stream << "Day " << std::format("{:2}", day.dayNo) << " - B: (" << std::format("{:10.4f}", day.ioResult.second.count()) << "ms + " << std::format("{:10.4f}", day.parseResult.second.count()) << "ms + " << std::format("{:10.4f}", day.partBResult.second.count()) << "ms): ";
            std::visit([&stream](const auto& v) { stream << v; }, day.partBResult.first);
            stream << "\n";

            return stream;
        }
    };
}
