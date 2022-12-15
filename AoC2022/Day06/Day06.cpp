#include "Day06.h"

#include <unordered_map>
#include <numeric>

namespace AoC2022 {
    namespace Day06 {
        size_t Run(const std::string& input, int sequenceLength) {
            size_t marker = 0;
            std::unordered_map<char, int> seenCharacters = {};
            for (marker = 0; marker < input.size(); marker++) {
                if(!seenCharacters.contains(input[marker])){ seenCharacters[input[marker]] = 0; }
                seenCharacters[input[marker]]++;
                if (seenCharacters.size() == sequenceLength) {
                    break;
                }
                else {
                    int startOfBlock = marker - (sequenceLength - 1);
                    if (startOfBlock >= 0) {
                        char firstCharInBlock = input[startOfBlock];
                        if (!--seenCharacters[firstCharInBlock]) {
                            seenCharacters.erase(firstCharInBlock);
                        }
                    }
                }
            }
            return marker + 1;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto marker = Run(input, 4);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { marker, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto marker = Run(input, 14);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { marker, endtime - startTime };
        }
    }
}