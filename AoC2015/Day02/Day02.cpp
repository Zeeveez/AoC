#include "Day02.h"
#include <numeric>

namespace AoC2015 {
    namespace Day02 {
        std::tuple<uint64_t, uint64_t, uint64_t> ReadBox(std::string str) {
            std::vector<uint64_t> vals = { 0, 0, 0 };
            std::size_t i = 0;
            for (auto& c : str) {
                switch (c) {
                case 'x':
                    i++;
                    break;
                default:
                    vals[i] = vals[i] * 10 + (c - '0');
                }
            }
            return { vals[0], vals[1], vals[2] };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t r = std::accumulate(
                input.begin(),
                input.end(),
                (uint64_t)0,
                [](uint64_t acc, std::string box) {
                    auto boxDims = ReadBox(box);
                    auto l = std::get<0>(boxDims);
                    auto w = std::get<1>(boxDims);
                    auto h = std::get<2>(boxDims);
                    auto lw = l * w;
                    auto wh = w * h;
                    auto hl = h * l;
                    auto smallest = std::min({ lw, wh, hl });
                    return acc + 2 * lw + 2 * wh + 2 * hl + smallest;
                });

            auto endTime = std::chrono::high_resolution_clock::now();
            return { r, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            uint64_t r = std::accumulate(
                input.begin(),
                input.end(),
                (uint64_t)0,
                [](uint64_t acc, std::string box) {
                    auto boxDims = ReadBox(box);
                    auto l = std::get<0>(boxDims);
                    auto w = std::get<1>(boxDims);
                    auto h = std::get<2>(boxDims);
                    auto highest = std::max({ l, w, h });
                    return acc + 2 * l + 2 * w + 2 * h - 2 * highest + l * w * h;
                });

            auto endTime = std::chrono::high_resolution_clock::now();
            return { r, endTime - startTime };
        }
    }
}