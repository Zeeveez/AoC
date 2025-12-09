#include <algorithm>
#include <numeric>

#include "Day09.h"

#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    AoC::DayResult::PuzzleResult Day09::A() {
        std::vector<std::pair<uint64_t, uint64_t>> files = {}; // ID, size

        for (int i = 0; i < rawData.size(); i++) {
            files.push_back({ i % 2 == 0 ? (i / 2) : std::numeric_limits<uint64_t>::max(), rawData[i] - '0' });
        }

        uint64_t res = 0;
        uint64_t blockIdx = 0;
        for (int i = 0; i < files.size(); i++) {
            if (files[i].first == std::numeric_limits<uint64_t>::max()) {
                while (files.back().first == std::numeric_limits<uint64_t>::max()) { files.pop_back(); }
                int moveAmount = std::min(files[i].second, files.back().second);
                res += (blockIdx * moveAmount + (moveAmount - 1) * (moveAmount) / 2) * files.back().first;
                files[i].second -= moveAmount;
                files.back().second -= moveAmount;
                blockIdx += moveAmount;
                if (files[i].second != 0) {
                    i--;
                    files.pop_back();
                }
            }
            else {
                res += (blockIdx * files[i].second + (files[i].second - 1) * (files[i].second) / 2) * files[i].first;
                blockIdx += files[i].second;
            }
        }

        return res;
    }

    AoC::DayResult::PuzzleResult Day09::B() {
        std::vector<std::pair<uint64_t, uint64_t>> files = {}; // ID, size

        for (int i = 0; i < rawData.size(); i++) {
            files.push_back({ i % 2 == 0 ? (i / 2) : std::numeric_limits<uint64_t>::max(), rawData[i] - '0' });
        }

        uint64_t res = 0;
        uint64_t blockIdx = 0;
        for (int i = 0; i < files.size(); i++) {
            if (files[i].first == std::numeric_limits<uint64_t>::max()) {
                int toFill = files[i].second;
                for (int j = files.size() - 1; j > i; j--) {
                    if (files[j].first != std::numeric_limits<uint64_t>::max() && files[j].first != std::numeric_limits<uint64_t>::min() && files[j].second && files[j].second <= toFill) {
                        res += (blockIdx * files[j].second + (files[j].second - 1) * (files[j].second) / 2) * files[j].first;
                        blockIdx += files[j].second;
                        toFill -= files[j].second;
                        files[j].first = std::numeric_limits<uint64_t>::min();
                        if (toFill == 0) {
                            break;
                        }
                    }
                }
                blockIdx += toFill;
            }
            else if (files[i].first == std::numeric_limits<uint64_t>::min()) {
                blockIdx += files[i].second;
            }
            else if (files[i].second) {
                res += (blockIdx * files[i].second + (files[i].second - 1) * (files[i].second) / 2) * files[i].first;
                blockIdx += files[i].second;
            }
        }

        return res;
    }
}