#include "Day08.h"

#include <numeric>
#include <unordered_map>

#include <iostream>
namespace AoC2015 {
    namespace Day08 {
        std::vector<std::pair<std::vector<int>, std::vector<int>>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::pair<std::vector<int>, std::vector<int>>> processedInput = {};

            int idx = 0;
            for (int i = 0; i < input.size() / 15; i++) {
                std::vector<unsigned char> inputs = {};
                std::vector<unsigned char> outputs = {};
                for (int j = 0; j < 10; j++) {
                    unsigned char val = 0;
                    for (auto& c : input[idx++]) {
                        val += 1 << (c - 'a');
                    }
                    inputs.push_back(val);
                }
                idx++;
                for (int j = 0; j < 4; j++) {
                    unsigned char val = 0;
                    for (auto& c : input[idx++]) {
                        val += 1 << (c - 'a');
                    }
                    outputs.push_back(val);
                }
                processedInput.push_back(DecodeLine({ inputs, outputs }));
            }

            return processedInput;
        }

        int CountBits(unsigned char input) {
            int c = 0;
            for (int i = 0; i < 8; i++) {
                if (((input >> i) & 1) == 1) {
                    c++;
                }
            }
            return c;
        }

        std::pair<std::vector<int>, std::vector<int>> DecodeLine(const std::pair<std::vector<unsigned char>, std::vector<unsigned char>>& input) {
            std::unordered_map<unsigned char, int> decoded = { };
            std::unordered_map<int, unsigned char> reverseDecoded = { };

            for (auto& c : input.first) {
                if (decoded.count(c) == 0 && CountBits(c) == 2) { decoded.insert({ c, 1 }); reverseDecoded.insert({ 1, c }); }
                if (decoded.count(c) == 0 && CountBits(c) == 4) { decoded.insert({ c, 4 }); reverseDecoded.insert({ 4, c }); }
                if (decoded.count(c) == 0 && CountBits(c) == 3) { decoded.insert({ c, 7 }); reverseDecoded.insert({ 7, c }); }
                if (decoded.count(c) == 0 && CountBits(c) == 7) { decoded.insert({ c, 8 }); reverseDecoded.insert({ 8, c }); }
            }

            for (auto& c : input.first) {
                if (decoded.count(c) == 0 && CountBits(c & ~reverseDecoded[1]) == 3) { decoded.insert({ c, 3 }); reverseDecoded.insert({ 3, c }); }
                if (decoded.count(c) == 0 && CountBits(c & ~reverseDecoded[1]) == 5) { decoded.insert({ c, 6 }); reverseDecoded.insert({ 6, c }); }
                if (decoded.count(c) == 0 && CountBits(c & reverseDecoded[4]) == 4) { decoded.insert({ c, 9 }); reverseDecoded.insert({ 9, c }); }
            }

            unsigned char code5 = reverseDecoded[6] & reverseDecoded[9];
            decoded.insert({ code5, 5 });
            reverseDecoded.insert({ 5, code5 });

            for (auto& c : input.first) {
                if (decoded.count(c) == 0 && CountBits(c & reverseDecoded[8]) == 6) { decoded.insert({ c, 0 }); reverseDecoded.insert({ 0, c }); }
                if (decoded.count(c) == 0 && CountBits(c & reverseDecoded[8]) == 5) { decoded.insert({ c, 2 }); reverseDecoded.insert({ 2, c }); }
            }

            std::vector<int> newInputs = {};
            for (auto& c : input.first) { newInputs.push_back(decoded[c]); }
            std::vector<int> newOutputs = {};
            for (auto& c : input.second) { newOutputs.push_back(decoded[c]); }

            return { newInputs, newOutputs };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto inputs = PreProcessInput(input);
            auto count = std::accumulate(inputs.begin(), inputs.end(), 0,
                                   [](int acc, auto v) {
                                       return acc + std::accumulate(v.second.begin(), v.second.end(), 0,
                                                                    [](int acc, auto v) {
                                                                        return acc + (v == 1 || v == 4 || v == 7 || v == 8);
                                                                    });
                                   });
            auto endTime = std::chrono::high_resolution_clock::now();
            return { count, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            auto inputs = PreProcessInput(input);
            auto code = std::accumulate(inputs.begin(), inputs.end(), 0,
                                   [](int acc, auto v) {
                                       return acc + v.second[0] * 1000 + v.second[1] * 100 + v.second[2] * 10 + v.second[3];
                                   });
            auto endTime = std::chrono::high_resolution_clock::now();
            return { code, endTime - startTime };
        }
    }
}