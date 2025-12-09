#include "Day02.h"

#include <algorithm>

namespace AoC2022 {
    namespace Day02 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<char>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int score = 0;
            for (size_t i = 0; i < input.size(); i += 2) {
                Shapes opponent = SHAPE_MAPPINGS[input[i]];
                Shapes me = SHAPE_MAPPINGS[input[i + 1]];
                score += SHAPE_SCORE[me];
                score += MATCH_SCORE[me][opponent];
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<char>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            int score = 0;
            for (size_t i = 0; i < input.size(); i += 2) {
                Shapes opponent = SHAPE_MAPPINGS[input[i]];
                Shapes me = MATCH_FIXING_SHAPE[OUTCOME_MAPPINGS[input[i+1]]][opponent];
                score += SHAPE_SCORE[me];
                score += MATCH_SCORE[me][opponent];
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { score, endTime - startTime };
        }
    }
}