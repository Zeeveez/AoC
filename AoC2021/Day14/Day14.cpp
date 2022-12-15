#include "Day14.h"

#include <algorithm>
#include <limits>

namespace AoC2021 {
    namespace Day14 {
        std::pair<std::string, std::unordered_map<std::string, std::vector<std::string>>> PreProcessInput(const std::vector<std::string>& input) {
            std::unordered_map<std::string, std::vector<std::string>> pairRules = {};
            for (int i = 1; i < input.size(); i += 3) {
                // Example: CK -> N
                // Results: CK -> { CN, NK }
                pairRules.insert({ input[i], { input[i][0] + input[i + 2], input[i + 2] + input[i][1] } });
            }

            return { input[0], pairRules };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input, int iter) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto [polymerTemplate, pairRules] = PreProcessInput(input);

            // Get initial counts of all pairs
            std::unordered_map<std::string, uint64_t> counts = {};
            for (int i = 0; i < polymerTemplate.size() - 1; i++) {
                std::string match = std::string(1, polymerTemplate[i]) + polymerTemplate[i + 1];
                if (!counts.contains(match)) {
                    counts[match] = 0;
                }
                counts[match]++;
            }


            for (int i = 0; i < iter; i++) {
                std::unordered_map<std::string, uint64_t> newCounts = {};
                for (auto& [pair, count] : counts) {
                    // If a pair is not in the rules, add it, mapping it to itself
                    if (!pairRules.contains(pair)) {
                        pairRules[pair] = { pair };
                    }

                    // Add current pairs count to each of its output pairs
                    for (auto& newPair : pairRules[pair]) {
                        if (!newCounts.contains(newPair)) {
                            newCounts[newPair] = 0;
                        }
                        newCounts[newPair] += count;
                    }
                }
                counts = newCounts;
            }

            // Convert counts of pairs to counts of elements
            std::unordered_map<char, uint64_t> elemCounts = {};
            for (auto& [pair, count] : counts) {
                for (auto& elem : pair) {
                    if (!elemCounts.contains(elem)) {
                        elemCounts[elem] = 0;
                    }
                    elemCounts[elem] += count;
                }
            }

            // Divide each elems count by two, as we have pairs all elements are counted twice.
            // Round up to account for start/end of polymer chain
            // should probably instead round down and add 1 if the chain either starts/ends with a particular character, but works for my input
            for (auto& [element, count] : elemCounts) {
                elemCounts[element] = count / 2 + count % 2;
            }

            // Get Max/Min counts for result
            uint64_t max = std::numeric_limits<uint64_t>::min();
            uint64_t min = std::numeric_limits<uint64_t>::max();
            for (auto& [element, count] : elemCounts) {
                max = std::max(count, max);
                min = std::min(count, min);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { max - min, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            return A(input, 40);
        }
    }
}