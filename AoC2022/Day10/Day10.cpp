#include "Day10.h"

#include "../../Helpers/Helpers.h"

namespace AoC2022 {
    namespace Day10 {
        void HandleCycleA(int64_t& x, int64_t& cycles, int64_t& res) {
            cycles++;
            if (cycles == 20 || cycles == 60 || cycles == 100 || cycles == 140 || cycles == 180 || cycles == 220) {
                res += cycles * x;
            }
        }

        void HandleCycleB(int64_t& x, int64_t& cycles, std::vector<std::vector<bool>>& resArray) {
            int pixelX = cycles % 40;
            int pixelY = cycles / 40;

            bool toDraw = false;
            if (pixelX == x - 1 || pixelX == x || pixelX == x + 1) {
                toDraw = true;
            }

            while (resArray.size() < pixelX + 1) {
                resArray.push_back({});
            }
            while (resArray[pixelX].size() < pixelY + 1) {
                resArray[pixelX].push_back(false);
            }
            resArray[pixelX][pixelY] = toDraw;

            cycles++;
        }

        std::pair<int64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int64_t res = 0;

            int64_t x = 1;
            int64_t cycles = 0;
            for (size_t i = 0; i < input.size(); i++) {
                if (input[i] == "noop") {
                    HandleCycleA(x, cycles, res);
                }
                else if (input[i] == "addx") {
                    int64_t toAdd = std::stoi(input[++i]);
                    HandleCycleA(x, cycles, res);
                    HandleCycleA(x, cycles, res);
                    x += toAdd;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<std::string, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int64_t x = 1;
            int64_t cycles = 0;
            std::vector<std::vector<bool>> resArray = { {} };
            for (size_t i = 0; i < input.size(); i++) {
                if (input[i] == "noop") {
                    HandleCycleB(x, cycles, resArray);
                }
                else if (input[i] == "addx") {
                    int64_t toAdd = std::stoi(input[++i]);
                    HandleCycleB(x, cycles, resArray);
                    HandleCycleB(x, cycles, resArray);
                    x += toAdd;
                }
            }

            std::string res = AoC::Helpers::ParseDrawnString(resArray);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}