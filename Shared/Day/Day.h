#pragma once
#include <string>
#include <format>
#include <vector>
#include <cstdint>
#include <chrono>
#include <functional>

#include "DayResult.h"

#include "../../Helpers/Helpers.h"

namespace AoC {
    template <class T, int yearNo, int dayNo>
    class Day {
    private:
        const std::string fileName = std::format("./{}/Day{:02}.txt", yearNo, dayNo);

    protected:
        T rawData;

        Day() {}

    private:
        std::chrono::duration<double, std::milli> TimeFunc(std::function<void()> f) {
            auto startTime = std::chrono::high_resolution_clock::now();
            f();
            auto endTime = std::chrono::high_resolution_clock::now();
            return endTime - startTime;
        }

        void RunPart(DayResult::PartResult& partResult, std::function<DayResult::PuzzleResult()> partFunc) {
            partResult.second = TimeFunc([&]() { partResult.first = partFunc(); });
        }

    public:
        DayResult Run() {
            DayResult results(dayNo);
            results.ioResult.second = TimeFunc([&]() { rawData = Load<T>(); });
            results.parseResult.second = TimeFunc([&]() { Parse(); });
            RunPart(results.partAResult, std::bind(&Day::A, this));
            Parse(); // Re-parse to clear any changes made
            RunPart(results.partBResult, std::bind(&Day::B, this));
            return results;
        }

    private:
        virtual void Parse() {};
        virtual DayResult::PuzzleResult A() { return 0; };
        virtual DayResult::PuzzleResult B() { return 0; };

        template<typename U>
        U Load() {}
        template<>
        std::vector<std::vector<std::uint64_t>> Load<std::vector<std::vector<std::uint64_t>>>() {
            return AoC::Helpers::ReadTokenGrid<std::uint64_t>(fileName);
        }
        template<>
        std::vector<std::vector<std::uint32_t>> Load<std::vector<std::vector<std::uint32_t>>>() {
            return AoC::Helpers::ReadTokenGrid<std::uint32_t>(fileName);
        }
        template<>
        std::vector<std::vector<std::uint16_t>> Load<std::vector<std::vector<std::uint16_t>>>() {
            return AoC::Helpers::ReadTokenGrid<std::uint16_t>(fileName);
        }
        template<>
        std::vector<std::uint64_t> Load<std::vector<std::uint64_t>>() {
            return AoC::Helpers::ReadTokens<std::uint64_t>(fileName);
        }
        template<>
        std::vector<std::uint32_t> Load<std::vector<std::uint32_t>>() {
            return AoC::Helpers::ReadTokens<std::uint32_t>(fileName);
        }
        template<>
        std::vector<std::int64_t> Load<std::vector<std::int64_t>>() {
            return AoC::Helpers::ReadCommaDelimitedList(fileName);
        }
        template<>
        std::vector<std::string> Load<std::vector<std::string>>() {
            return AoC::Helpers::ReadLines(fileName);
        }
        template<>
        std::string Load<std::string>() {
            return AoC::Helpers::ReadToken<std::string>(fileName);
        }
    };
}
