#ifndef DAY20_H
#define DAY20_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day20 {
        std::pair<std::vector<bool>, std::vector<std::vector<bool>>> PreProcessInput(const std::vector<std::string>& input);

        bool GetPixel(const std::vector<bool>& convolutionConfig, const std::vector<std::vector<bool>>& image, int generation, size_t x, size_t y, int dx, int dy);
        bool GetPixel(const std::vector<bool>& convolutionConfig, const std::vector<std::vector<bool>>& image, int generation, size_t x, size_t y);
        std::vector<std::vector<bool>> Convolute(const std::vector<bool>& convolutionConfig, const std::vector<std::vector<bool>>& image, int generation);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input, int genCount = 2);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif