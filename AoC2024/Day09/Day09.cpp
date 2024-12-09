#include "Day09.h"

#include <limits>
#include <algorithm>
#include <numeric>
#include <iostream>

namespace AoC2024 {
    namespace Day09 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            std::vector<uint64_t> files = {};

            for (int i = 0; i < input.size(); i++) {
                for (int j = 0; j < input[i] - '0'; j++) {
                    files.push_back(i % 2 == 0 ? (i / 2) : std::numeric_limits<uint64_t>::max());
                }
            }

            for (int i = files.size() - 1; i >= 0; i--) {
                if (files[i] == std::numeric_limits<uint64_t>::max()) { continue; }
                size_t freeSpace = 0;
                while (files[freeSpace] != std::numeric_limits<uint64_t>::max()) { freeSpace++; }
                if (i < freeSpace) { break; }
                files[freeSpace] = files[i];
                files[i] = std::numeric_limits<uint64_t>::max();
            }

            uint64_t res = 0;
            for (int i = 0; i < files.size(); i++) {
                if (files[i] == std::numeric_limits<uint64_t>::max()) { break; }
                res += files[i] * i;
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            std::vector<std::pair<uint64_t, uint64_t>> files = {}; // ID, size

            uint64_t maxID = 0;
            for (int i = 0; i < input.size(); i++) {
                files.push_back({ i % 2 == 0 ? (i / 2) : std::numeric_limits<uint64_t>::max(), input[i] - '0'});
                maxID = std::max(maxID, i % 2 == 0 ? (i / 2) : 0ull);
            }
           
            for (int i = maxID; i >= 0; i--) {
                for (int j = 0; j < files.size(); j++) {
                    if (files[j].first == i) {
                        for (int k = 0; k < files.size() && k < j; k++) {
                            if (files[k].first == std::numeric_limits<uint64_t>::max() && files[k].second >= files[j].second) {
                                files[k].second -= files[j].second;
                                files.insert(files.begin() + k, { files[j].first, files[j].second });
                                files[j + 1].first = std::numeric_limits<uint64_t>::max();
                                break;
                            }
                        }
                        for (int k = 0; k < files.size() - 1; k++) {
                            if (files[k].first == std::numeric_limits<uint64_t>::max() && files[k + 1].first == std::numeric_limits<uint64_t>::max()) {
                                files[k].second += files[k + 1].second;
                                files.erase(files.begin() + k + 1);
                                k--;
                            }
                        }
                    }
                }
            }


            std::vector<uint64_t> blocks = {};

            for (int i = 0; i < files.size(); i++) {
                for (int j = 0; j < files[i].second; j++) {
                    blocks.push_back(files[i].first);
                }
            }

            uint64_t res = 0;
            for (int i = 0; i < blocks.size(); i++) {
                if (blocks[i] == std::numeric_limits<uint64_t>::max()) { continue; }
                res += blocks[i] * i;
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}