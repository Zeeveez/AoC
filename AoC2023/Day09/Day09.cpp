#include "Day09.h"

#include <iostream>
#include <numeric>

namespace AoC2023::Day09 {
    std::vector<int64_t> ParseLine(const std::string& input) {
        std::vector<int64_t> data = {};

        std::istringstream iss(input);
        int64_t token;
        while (iss >> token) {
            data.push_back(token);
        }

        return data;
    }

    int64_t Process(const std::vector<int64_t>& data, const ExtrapolationFunction& extrapFunc) {
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

    int64_t ExtrapolateA(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s) {
        if (all0s) {
            return data[data.size() - 1];
        }
        else {
            return data[data.size() - 1] + Process(newData, ExtrapolateA);
        }
    }

    int64_t ExtrapolateB(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s) {
        if (all0s) {
            return data[0];
        }
        else {
            return data[0] - Process(newData, ExtrapolateB);
        }
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> Solve(const std::vector<std::string>& input, const ExtrapolationFunction& extrapFunc) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        int64_t score = 0;
        for (auto& line : input) {
            auto data = ParseLine(line);

            score += Process(data, extrapFunc);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        return Solve(input, ExtrapolateA);
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        return Solve(input, ExtrapolateB);
    }
}