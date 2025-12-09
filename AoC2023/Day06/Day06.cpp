#include "Day06.h"

#include <cmath>

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day06::Load() {
        input = AoC::Helpers::ReadLines("./Day06.txt");
    }

    void Day06::Parse() {
        // No parsing required
    }

    void Day06::A() {
        auto races = ParseInput(input);
        size_t res = 1;
        for (auto& race : races) {
            res *= CountWins(race.first, race.second);
        }
        partAResult.first = res;
    }

    void Day06::B() {
        auto races = ParseInput(input, true);
        size_t res = CountWins(races[0].first, races[0].second);
        partBResult.first = res;
    }

    std::vector<uint64_t> Day06::ParseLine(const std::string& input, bool partB) {
        std::istringstream iss(input);
        std::string temp;
        iss >> temp; // Discard label

        std::vector<uint64_t> values = {};
        if (!partB) {
            uint64_t token;
            while (iss >> token) {
                values.push_back(token);
            }
        }
        else {
            std::string v = "";
            while (iss >> temp) {
                v += temp;
            }
            values.push_back(std::stoll(v));
        }

        return values;
    }

    std::vector<std::pair<uint64_t, uint64_t>> Day06::ParseInput(const std::vector<std::string>& input, bool partB) {
        auto times = ParseLine(input[0], partB);
        auto distances = ParseLine(input[1], partB);

        std::vector<std::pair<uint64_t, uint64_t>> races = {};

        for (size_t i = 0; i < times.size(); i++) {
            races.push_back({ times[i], distances[i] });
        }

        return races;
    }

    uint64_t Day06::CountWins(uint64_t time, uint64_t record) {
        // Brute force
        //size_t count = 0;
        //for (size_t i = 1; i < time; i++) {
        //    size_t distance = (time - i) * i;
        //    count += distance > record ? 1 : 0;
        //}
        //return count;

        double requiredWait = (time - std::sqrt(time * time - 4 * record)) / 2;
        uint64_t minWait = std::ceil(requiredWait);
        uint64_t maxWait = time - minWait;
        return maxWait - minWait + 1;
    }
}