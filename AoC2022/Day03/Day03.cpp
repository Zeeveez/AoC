#include "Day03.h"

#include <algorithm>
#include <set>

namespace AoC2022 {
    namespace Day03 {
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int result = 0;
            for (auto& line : input) {
                std::string a = line.substr(0, line.length() / 2);
                std::string b = line.substr(line.length() / 2);

                std::set<char> aChar;
                for (auto& c : a) { aChar.insert(c); }
                std::set<char> bChar;
                for (auto& c : b) { bChar.insert(c); }

                std::vector<char> both;
                std::set_intersection(aChar.begin(), aChar.end(), bChar.begin(), bChar.end(), std::inserter(both, both.begin()));

                char res = both[0];
                if (res >= 'a' && res <= 'z') { result += res - 'a' + 1; }
                if (res >= 'A' && res <= 'Z') { result += res - 'A' + 27; }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { result, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            int result = 0;
            for (size_t i = 0; i < input.size(); i += 3) {
                std::set<char> aChar;
                for (auto& c : input[i]) { aChar.insert(c); }
                std::set<char> bChar;
                for (auto& c : input[i + 1]) { bChar.insert(c); }
                std::set<char> cChar;
                for (auto& c : input[i + 2]) { cChar.insert(c); }

                std::set<char> aAndB;
                std::set_intersection(aChar.begin(), aChar.end(), bChar.begin(), bChar.end(), std::inserter(aAndB, aAndB.begin()));
                std::vector<char> all3;
                std::set_intersection(aAndB.begin(), aAndB.end(), cChar.begin(), cChar.end(), std::inserter(all3, all3.begin()));

                char res = all3[0];
                if (res >= 'a' && res <= 'z') { result += res - 'a' + 1; }
                if (res >= 'A' && res <= 'Z') { result += res - 'A' + 27; }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { result, endtime - startTime };
        }
    }
}