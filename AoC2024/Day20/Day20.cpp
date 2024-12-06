#include "Day20.h"

#include <iostream>
#include <cmath>

namespace AoC2022 {
    namespace Day20 {
        std::pair<std::unordered_map<int64_t, int64_t>, std::vector<int64_t>> PreProcessInput(const std::vector<int>& input) {
            std::unordered_map<int64_t, int64_t> indexMappings = {};
            std::vector<int64_t> indices = {};
            for (auto& i : input) {
                indexMappings[indices.size()] = i;
                indices.push_back(indices.size());
            }
            return { indexMappings, indices };
        }

        int GetResult(const std::unordered_map<int64_t, int64_t>& indexMappings, const std::vector<int64_t>& indices) {
            int zeroIdx = 0;
            for (auto& item : indices) {
                if (indexMappings.at(item) == 0) {
                    zeroIdx = item;
                    break;
                }
            }
            auto pos = std::distance(indices.begin(), std::find(indices.begin(), indices.end(), zeroIdx));
            int64_t res =
                indexMappings.at(indices.at((pos + 1000) % indices.size()))
                + indexMappings.at(indices.at((pos + 2000) % indices.size()))
                + indexMappings.at(indices.at((pos + 3000) % indices.size()));

            return res;
        }

        void MoveItem(std::vector<int64_t>& list, int64_t item, int64_t moves) {
            if (moves < 0) { moves += (list.size() - 1) * std::abs(moves); }
            auto pos = std::distance(list.begin(), std::find(list.begin(), list.end(), item));
            int64_t newPos = pos + moves;
            newPos %= list.size() - 1;
            list.erase(list.begin() + pos);
            list.insert(list.begin() + newPos, item);
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<int>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [indexMappings, indices] = PreProcessInput(input);
            auto list = indices;

            for (auto& item : indices) {
                MoveItem(list, item, indexMappings[item]);
            }

            int64_t res = GetResult(indexMappings, list);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<int>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto [indexMappings, indices] = PreProcessInput(input);
            for (auto& kvp : indexMappings) {
                kvp.second *= (int64_t)811589153;
            }
            auto list = indices;

            for (int i = 0; i < 10; i++) {
                for (auto& item : indices) {
                    MoveItem(list, item, indexMappings[item]);
                }
            }

            int64_t res = GetResult(indexMappings, list);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}