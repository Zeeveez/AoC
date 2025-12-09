#include "Day23.h"
#include "../../Helpers/Helpers.h"

#include <algorithm>
#include <iterator>
#include <sstream>

namespace AoC2024 {
    void Day23::Parse() {
        for (auto& line : rawData) {
            int a = (line[0] - 'a') * 26 + line[1] - 'a';
            int b = (line[3] - 'a') * 26 + line[4] - 'a';
            if (!map.contains(a)) {
                map[a] = {};
            }
            map[a].insert(b);
            if (!map.contains(b)) {
                map[b] = {};
            }
            map[b].insert(a);
        }
    }

    std::string Day23::IDToString(int id) {
        std::string out = "";
        out.push_back((char)(id / 26 + 'a'));
        out.push_back((char)(id % 26 + 'a'));
        return out;
    }

    AoC::DayResult::PuzzleResult Day23::A() {
        std::unordered_set<int> seen = {};
        for (auto& [k, v] : map) {
            if (k / 26 + 'a' != 't') { continue; }

            for (auto& connection : v) {
                for (auto& subconnection : map[connection]) {
                    if (map[subconnection].contains(k)) {
                        int max = std::max(k, std::max(connection, subconnection));
                        int min = std::min(k, std::min(connection, subconnection));
                        int mid = k + connection + subconnection - max - min;
                        seen.insert(max * 26 * 26 * 26 * 26 + mid * 26 * 26 + min);
                    }
                }
            }
        }

        uint64_t res = seen.size();
        return res;
    }

    AoC::DayResult::PuzzleResult Day23::B() {
        std::unordered_set<int> biggestConnection = {};

        for (auto& [k, v] : map) {
            std::unordered_set<int> testComputers = v;

            std::unordered_map<int, int> possibleConnections = {};
            for (auto& testComputer : testComputers) {
                possibleConnections[testComputer] = 1;
            }
            possibleConnections[k] = 0;

            testComputers.insert(k);


            for (auto& computer : testComputers) {
                for (auto& connection : map[computer]) {
                    if (possibleConnections.contains(connection)) {
                        possibleConnections[connection]++;
                    }
                }
            }


            std::vector<int> counts(possibleConnections.size() + 1, 0);
            for (auto& [k, v] : possibleConnections) {
                counts[v]++;
            }
            int max = *std::max_element(counts.begin(), counts.end());

            if (max > biggestConnection.size()) {
                biggestConnection = {};
                for (auto& [k, v] : possibleConnections) {
                    if (v == max) {
                        biggestConnection.insert(k);
                    }
                }
            }
        }

        std::vector<std::string> result = {};
        for (auto& k : biggestConnection) {
            result.push_back(IDToString(k));
        }
        std::sort(result.begin(), result.end());

        std::ostringstream joinedString;
        std::copy(result.begin(), result.end(), std::ostream_iterator<std::string>(joinedString, ","));
        std::string res = joinedString.str();
        res.pop_back();

        return res;
    }
}