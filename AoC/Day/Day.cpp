#include <ostream>
#include <format>
#include <variant>

#include "Day.h"

namespace AoC {
    Day::Day() {}

    std::chrono::duration<double, std::milli> Day::TimeFunc(std::function<void()> f) {
        auto startTime = std::chrono::high_resolution_clock::now();
        f();
        auto endTime = std::chrono::high_resolution_clock::now();
        return endTime - startTime;
    }

    std::ostream& operator<<(std::ostream& stream, const Day& day)
    {
        stream << "Day " << std::format("{:2}", day.dayNo) << " - A: (" << std::format("{:10.4f}", day.partAResult.second.count()) << "ms + " << std::format("{:10.4f}", day.parseResult.second.count()) << "ms): ";
        std::visit([&stream](const auto& v) { stream << v; }, day.partAResult.first);
        stream << "\n";

        stream << "Day " << std::format("{:2}", day.dayNo) << " - B: (" << std::format("{:10.4f}", day.partBResult.second.count()) << "ms + " << std::format("{:10.4f}", day.parseResult.second.count()) << "ms): ";
        std::visit([&stream](const auto& v) { stream << v; }, day.partBResult.first);
        stream << "\n";

        return stream;
    }
}