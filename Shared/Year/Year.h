#pragma once
#include <vector>
#include <chrono>
#include <format>

#include "../Day/Day.h"

namespace AoC {
    template <int yearNo>
    class Year {
    public:
        std::vector<DayResult> days = {};
        const int year = yearNo;
        Year() { }

        friend std::ostream& operator<<(std::ostream& stream, const Year& year)
        {
            std::chrono::duration<double, std::milli> totalAIOTime = std::chrono::duration<double, std::milli>(0);
            std::chrono::duration<double, std::milli> totalAParseTime = std::chrono::duration<double, std::milli>(0);
            std::chrono::duration<double, std::milli> totalARunTime = std::chrono::duration<double, std::milli>(0);

            std::chrono::duration<double, std::milli> totalBIOTime = std::chrono::duration<double, std::milli>(0);
            std::chrono::duration<double, std::milli> totalBParseTime = std::chrono::duration<double, std::milli>(0);
            std::chrono::duration<double, std::milli> totalBRunTime = std::chrono::duration<double, std::milli>(0);

            std::chrono::duration<double, std::milli> totalIOTime = std::chrono::duration<double, std::milli>(0);
            std::chrono::duration<double, std::milli> totalParseTime = std::chrono::duration<double, std::milli>(0);
            std::chrono::duration<double, std::milli> totalRunTime = std::chrono::duration<double, std::milli>(0);

            stream << "                             Advent of Code " << year.year << "\n";
            stream << "=================================================================================" << "\n\n";
            stream << "  Day/Part: (    I/O Time +   Parse Time +     Run Time): Result" << "\n";
            for (auto& day : year.days) {
                stream << day;

                totalAIOTime += day.ioResult.second;
                totalAParseTime += day.parseResult.second;
                totalARunTime += day.partAResult.second;

                totalBIOTime += day.ioResult.second;
                totalBParseTime += day.parseResult.second;
                totalBRunTime += day.partBResult.second;

                totalIOTime += day.ioResult.second * 2;
                totalParseTime += day.parseResult.second * 2;
                totalRunTime += day.partAResult.second + day.partBResult.second;
            }

            stream << "\n";
            stream << "   Total A:  " << std::format("{:10.4f}", totalAIOTime.count()) << "ms + " << std::format("{:10.4f}", totalAParseTime.count()) << "ms + " << std::format("{:10.4f}", totalARunTime.count()) << "ms : " << std::format("{:10.4f}", (totalAIOTime + totalAParseTime + totalARunTime).count()) << "ms\n";
            stream << "   Total B:  " << std::format("{:10.4f}", totalBIOTime.count()) << "ms + " << std::format("{:10.4f}", totalBParseTime.count()) << "ms + " << std::format("{:10.4f}", totalBRunTime.count()) << "ms : " << std::format("{:10.4f}", (totalAIOTime + totalAParseTime + totalBRunTime).count()) << "ms\n";
            stream << "     Total:  " << std::format("{:10.4f}", totalIOTime.count()) << "ms + " << std::format("{:10.4f}", totalParseTime.count()) << "ms + " << std::format("{:10.4f}", totalRunTime.count()) << "ms : " << std::format("{:10.4f}", (totalIOTime + totalParseTime + totalRunTime).count()) << "ms\n";

            return stream;
        }
    };
}
