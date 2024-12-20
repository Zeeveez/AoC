#include <ostream>
#include <format>
#include <variant>

#include "Day.h"

namespace AoC {
    Day::Day(int dayNo) : dayNo(dayNo) {}

    std::ostream& operator<<(std::ostream& stream, const Day& day)
    {
        stream << "Day " << std::format("{:2}", day.dayNo) << " - A (" << std::format("{:10.4f}", day.partAResult.second.count()) << "ms): ";
        std::visit([&stream](const auto& v) { stream << v; }, day.partAResult.first);
        stream << "\n";

        stream << "Day " << std::format("{:2}", day.dayNo) << " - B (" << std::format("{:10.4f}", day.partBResult.second.count()) << "ms): ";
        std::visit([&stream](const auto& v) { stream << v; }, day.partBResult.first);
        stream << "\n";

        return stream;
    }
}