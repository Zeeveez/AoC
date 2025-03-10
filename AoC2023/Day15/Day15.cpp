#include <sstream>
#include <map>

#include "Day15.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day15::Load() {
        input = AoC::Helpers::ReadToken<std::string>("./Day15.txt");
    }

    void Day15::Parse() {
        std::istringstream iss(input);
        std::string s;

        while (std::getline(iss, s, ',')) {
            strings.push_back(s);
        }
    }

    void Day15::A() {
        uint64_t res = 0;
        for (auto& str : strings) {
            res += Hash(str);
        }
        partAResult.first = res;
    }

    void Day15::B() {
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
                    boxes[box][label] = { val, boxes[box].size() + 1 };
                }
            }
            else {
                if (boxes.contains(box) && boxes[box].contains(label)) {
                    size_t pos = boxes[box][label].second;
                    boxes[box].erase(label);
                    for (auto& [otherLabel, otherBox] : boxes[box]) {
                        if (otherBox.second > pos) {
                            otherBox.second--;
                        }
                    }
                }
            }
        }

        uint64_t res = 0;
        for (auto& [boxNo, boxContents] : boxes) {
            for (auto& [label, lens] : boxContents) {
                res += (boxNo + 1) * lens.second * lens.first;
            }
        }
        partBResult.first = res;
    }

    size_t Day15::Hash(std::string str) {
        size_t v = 0;
        for (auto& c : str) {
            v += c;
            v *= 17;
            v %= 256;
        }
        return v;
    }
}