#include "Day15.h"

#include <iostream>
#include <numeric>
#include <map>

namespace AoC2023::Day15 {
    std::vector<std::string> ParseInput(const std::string& input) {
        std::vector<std::string> strings = {};
        std::istringstream iss(input);
        std::string s;

        while (std::getline(iss, s, ',')) {
            strings.push_back(s);
        }

        return strings;
    }

    size_t Hash(std::string str) {
        size_t v = 0;
        for (auto& c : str) {
            v += c;
            v *= 17;
            v %= 256;
        }
        return v;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto strings = ParseInput(input[0]);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t score = 0;
        for (auto& str : strings) {
            score += Hash(str);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto strings = ParseInput(input[0]);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        std::map<size_t, std::map<std::string, std::pair<size_t, size_t>>> boxes = {};
        for (auto& str : strings) {
            bool isAssign = str.find('=') != std::string::npos;
            size_t sepPos = isAssign ? str.find('=') : str.find('-');
            std::string label = str.substr(0, sepPos);
            size_t box = Hash(label);


            if (isAssign) {
                size_t val = std::stoi(str.substr(sepPos + 1));

                if (!boxes.contains(box)) { boxes[box] = {}; }

                if (boxes[box].contains(label)) {
                    boxes[box][label] = { val, boxes[box][label].second };
                }
                else {
                    boxes[box][label] = { val, boxes[box].size() + 1};
                }
            }
            else {
                if (boxes.contains(box) && boxes[box].contains(label)) {
                    size_t pos = boxes[box][label].second;
                    boxes[box].erase(label);
                    for (auto& [otherLabel, otherBox] : boxes[box]) {
                        if(otherBox.second > pos){
                            otherBox.second--;
                        }
                    }
                }
            }
        }

        uint64_t score = 0;
        for (auto& [boxNo, boxContents] : boxes) {
            for (auto& [label, lens] : boxContents) {
                score += (boxNo + 1) * lens.second * lens.first;
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}