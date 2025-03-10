#pragma once
#include <functional>
#include <cstdint>
#include <vector>
#include <string>

#include "../../AoC/Day/Day.h"

namespace AoC2023 {
    class Day09 : public AoC::Day {
    private:
        typedef std::function<int64_t(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s)> ExtrapolationFunction;

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day09() : Day() {
            dayNo = 9;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::vector<std::vector<int64_t>> data = {};

        uint64_t Solve(const ExtrapolationFunction& extrapFunc);

        static int64_t Process(const std::vector<int64_t>& data, const ExtrapolationFunction& extrapFunc);
        static int64_t ExtrapolateA(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s);
        static int64_t ExtrapolateB(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s);
    };
}