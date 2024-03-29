#ifndef DAY09_H
#define DAY09_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <unordered_map>
#include <functional>

namespace AoC2023::Day09 {
    typedef std::function<int64_t(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s)> ExtrapolationFunction;

    std::vector<int64_t> ParseLine(const std::string& input);
    int64_t Process(const std::vector<int64_t>& data, const ExtrapolationFunction& extrapFunc);
    int64_t ExtrapolateA(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s);
    int64_t ExtrapolateB(const std::vector<int64_t>& data, const std::vector<int64_t>& newData, bool all0s);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> Solve(const std::vector<std::string>& input, const ExtrapolationFunction& extrapFunc);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif