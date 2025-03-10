#include <sstream>

#include "Day09.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day09::Load() {
        input = AoC::Helpers::ReadLines("./Day09.txt");
    }

    void Day09::Parse() {
        for (auto& line : input) {
            data.push_back({});
            std::istringstream iss(line);
            int64_t token;
            while (iss >> token) {
                data.back().push_back(token);
            }
        }
    }

    void Day09::A() {
        partAResult.first = Solve(ExtrapolateA);
    }

    void Day09::B() {
        partBResult.first = Solve(ExtrapolateB);
    }

    uint64_t Day09::Solve(const ExtrapolationFunction& extrapFunc) {
        int64_t res = 0;
        for (auto& row : data) {
            res += Process(row, extrapFunc);
        }
        return res;
    }

    int64_t Day09::Process(const std::vector<int64_t>& data, const ExtrapolationFunction& extrapFunc) {
        bool all0s = true;
        std::vector<int64_t> newData = {};
        for (size_t i = 0; i < data.size() - 1; i++) {
            newData.push_back(data[i + 1] - data[i]);
            if (newData[newData.size() - 1] != 0) {
                all0s = false;
            }
        }

        return extrapFunc(data, newData, all0s);
    }

    int64_t Day09::ExtrapolateA(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s) {
        if (all0s) {
            return data[data.size() - 1];
        }
        else {
            return data[data.size() - 1] + Process(newData, ExtrapolateA);
        }
    }

    int64_t Day09::ExtrapolateB(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s) {
        if (all0s) {
            return data[0];
        }
        else {
            return data[0] - Process(newData, ExtrapolateB);
        }
    }
}