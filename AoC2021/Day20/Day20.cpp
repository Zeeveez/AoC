#include "Day20.h"

namespace AoC2021 {
    namespace Day20 {
        std::pair<std::vector<bool>, std::vector<std::vector<bool>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<bool> convolutionConfig = {};
            for (auto& c : input[0]) {
                convolutionConfig.push_back(c == '#');
            }

            std::vector<std::vector<bool>> image = {};
            for (int i = 1; i < input.size(); i++) {
                image.push_back({});
                for (auto& c : input[i]) {
                    image[image.size() - 1].push_back(c == '#');
                }
            }

            return { convolutionConfig, image };
        }

        bool GetPixel(const std::vector<bool>& convolutionConfig, const std::vector<std::vector<bool>>& image, int generation, size_t x, size_t y, int dx, int dy) {
            if (x + dx < 0 || x + dx >= image[0].size() || y + dy < 0 || y + dy >= image.size()) {
                return convolutionConfig[0] ? generation % 2 == 1 : false;
            }
            return image[y + dy][x + dx];
        }

        bool GetPixel(const std::vector<bool>& convolutionConfig, const std::vector<std::vector<bool>>& image, int generation, size_t x, size_t y) {
            size_t convoluteIdx = 0;
            for (int dy = -1; dy < 2; dy++) {
                for (int dx = -1; dx < 2; dx++) {
                    convoluteIdx <<= 1;
                    convoluteIdx += GetPixel(convolutionConfig, image, generation, x, y, dx, dy) ? 1 : 0;
                }
            }
            return convolutionConfig[convoluteIdx];
        }

        std::vector<std::vector<bool>> Convolute(const std::vector<bool>& convolutionConfig, const std::vector<std::vector<bool>>& image, int generation) {
            std::vector<std::vector<bool>> newImage = {};
            for (int y = -1; y < (int)image.size() + 1; y++) {
                newImage.push_back({});
                for (int x = -1; x < (int)image[0].size() + 1; x++) {
                    newImage[newImage.size() - 1].push_back(GetPixel(convolutionConfig, image, generation, x, y));
                }
            }
            return newImage;
        }

        uint64_t Count(const std::vector<std::vector<bool>>& image) {
            uint64_t c = 0;
            for (int y = 0; y < image.size(); y++) {
                for (int x = 0; x < image[0].size(); x++) {
                    if (image[y][x]) { c++; }
                }
            }
            return c;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input, int genCount) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto [convolutionConfig, image] = PreProcessInput(input);
            for (int i = 0; i < genCount; i++) {
                image = Convolute(convolutionConfig, image, i);
            }
            auto count = Count(image);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { count, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            return A(input, 50);
        }
    }
}