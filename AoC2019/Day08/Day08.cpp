#include "Day08.h"
#include "../../Helpers/Helpers.h"

namespace AoC2019 {
    AoC::DayResult::PuzzleResult Day08::A() {
        std::vector<std::vector<std::vector<int>>> img = CreateImage(rawData, 25, 6);

        int min0s = 99999999;
        int count1s = 0;
        int count2s = 0;
        for (auto& layer : img) {
            int no0s = 0;
            int no1s = 0;
            int no2s = 0;
            for (auto& col : layer) {
                for (auto& pixel : col) {
                    no0s += pixel == 0 ? 1 : 0;
                    no1s += pixel == 1 ? 1 : 0;
                    no2s += pixel == 2 ? 1 : 0;
                }
            }
            if (no0s < min0s) {
                min0s = no0s;
                count1s = no1s;
                count2s = no2s;
            }
        }
        return count1s * count2s;
    }

    AoC::DayResult::PuzzleResult Day08::B() {
        std::vector<std::vector<int>> img = FlattenLayers(CreateImage(rawData, 25, 6));
        std::string output = "";
        for (size_t y = 0; y < img[0].size(); y++) {
            for (size_t x = 0; x < img.size(); x++) {
                output += (img[x][y] == 0 ? ' ' : '#');
            }
        }
        return AoC::Helpers::ParseDrawnString(output, 5);
    }

    std::vector<std::vector<std::vector<int>>> Day08::CreateImage(std::string imgData, int width, int height) {
        std::vector<std::vector<std::vector<int>>> img = {};
        for (size_t layerNo = 0; layerNo < imgData.size() / (width * height); layerNo++) {
            std::vector<std::vector<int>> layer = {};
            for (int x = 0; x < width; x++) {
                std::vector<int> col = {};
                for (int y = 0; y < height; y++) {
                    col.push_back(imgData[layerNo * width * height + width * y + x] - '0');
                }
                layer.push_back(col);
            }
            img.push_back(layer);
        }
        return img;
    }

    std::vector<std::vector<int>> Day08::FlattenLayers(std::vector<std::vector<std::vector<int>>> img) {
        std::vector<std::vector<int>> flattenedImage = {};
        for (size_t x = 0; x < img[0].size(); x++) {
            std::vector<int> col = {};
            for (size_t y = 0; y < img[0][x].size(); y++) {
                for (size_t layer = 0; layer < img.size(); layer++) {
                    if (img[layer][x][y] != 2) {
                        col.push_back(img[layer][x][y]);
                        break;
                    }
                }
            }
            flattenedImage.push_back(col);
        }
        return flattenedImage;
    }
}