#include <numeric>

#include "Day06.h"

namespace AoC2019 {
    void Day06::Parse() {
        for (auto& line : rawData) {
            std::string str1;
            std::string str2;
            bool flag = false;
            for (auto& c : line) {
                if (c == ')') { flag = true; }
                else if (!flag) { str1 += c; }
                else { str2 += c; }
            }
            orbits.push_back({ str1, str2 });
        }
    }

    AoC::DayResult::PuzzleResult Day06::A() {
        std::unordered_map<std::string, std::string> orbitMap = MakeOrbitMap(orbits);
        return std::accumulate(orbitMap.begin(), orbitMap.end(), 0,
                               [&](int acc, auto node) {return acc + GetOrbitPath(orbitMap, node.first).size(); });
    }

    AoC::DayResult::PuzzleResult Day06::B() {
        std::unordered_map<std::string, std::string> orbitMap = MakeOrbitMap(orbits);

        std::vector<std::string> SAN_path = GetOrbitPath(orbitMap, "SAN");
        std::vector<std::string> YOU_path = GetOrbitPath(orbitMap, "YOU");

        while (SAN_path.back() == YOU_path.back()) {
            SAN_path.pop_back();
            YOU_path.pop_back();
        }

        return SAN_path.size() + YOU_path.size() - 2;
    }

    std::unordered_map<std::string, std::string> Day06::MakeOrbitMap(std::vector<std::tuple<std::string, std::string>>& orbits) {
        std::unordered_map<std::string, std::string> orbitMap = {};
        for (auto& orbit : orbits) {
            orbitMap[std::get<1>(orbit)] = std::get<0>(orbit);
        }
        return orbitMap;
    }

    std::vector<std::string> Day06::GetOrbitPath(std::unordered_map<std::string, std::string>& orbitMap, std::string node) {
        std::vector<std::string> orbitPath = {};
        while (orbitMap.count(node) == 1) {
            orbitPath.push_back(node);
            node = orbitMap[node];
        }
        return orbitPath;
    }
}