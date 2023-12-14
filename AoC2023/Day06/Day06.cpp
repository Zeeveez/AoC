#include "Day06.h"

#include <iostream>

namespace AoC2023::Day06 {
    std::vector<uint64_t> ParseLine(const std::string& input, bool partB) {
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

    std::vector<std::pair<uint64_t, uint64_t>> ParseInput(const std::vector<std::string>& input, bool partB) {
        auto times = ParseLine(input[0], partB);
        auto distances = ParseLine(input[1], partB);

        std::vector<std::pair<uint64_t, uint64_t>> races = {};

        for (size_t i = 0; i < times.size(); i++) {
            races.push_back({ times[i], distances[i] });
        }

        return races;
    }

    uint64_t CountWins(uint64_t time, uint64_t record) {
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

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto races = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        size_t score = 1;
        for (auto& race : races) {
            score *= CountWins(race.first, race.second);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto races = ParseInput(input, true);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        size_t score = CountWins(races[0].first, races[0].second);

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}