#include <stack>

#include "Day11.h"

namespace AoC2025 {
    void Day11::Parse() {
        map = {};
        ids = {};

        for (auto& line : rawData) {
            std::string src = "";
            std::string id = "";
            for (auto& c : line) {
                if (std::isalpha(c)) { id += c; }
                else if (id != "") {
                    if (!ids.contains(id)) { ids[id] = ids.size(); }
                    if (src == "") { src = id; }
                    else {
                        if (!map.contains(ids[src])) { map[ids[src]] = {}; }
                        map[ids[src]].insert(ids[id]);
                    }
                    id = "";
                }
            }
            if (id != "") {
                if (!ids.contains(id)) { ids[id] = ids.size(); }
                if (src == "") { src = id; }
                else {
                    if (!map.contains(ids[src])) { map[ids[src]] = {}; }
                    map[ids[src]].insert(ids[id]);
                }
            }
        }

        you = ids["you"];
        out = ids["out"];
        srv = ids["svr"];
        dac = ids["dac"];
        fft = ids["fft"];
    }

    AoC::DayResult::PuzzleResult Day11::A() {
        return CountRoutes(you, out);
    }

    AoC::DayResult::PuzzleResult Day11::B() {
        std::uint64_t res = 1;
        auto nodesReachableFromDAC = NodesReachableFrom(dac);
        auto nodesReachableFromFFT = NodesReachableFrom(fft);

        std::unordered_set<int> nodesToRemove = {};

        if (nodesReachableFromDAC.size() > nodesReachableFromFFT.size()) {
            // DAC comes first, get routes from FFT to OUT
            res *= CountRoutes(fft, out);
            // Remove all nodes after FFT, and make FFT the new OUT
            CollapseMap(fft, out);
            // DAC now only required node
            res *= CountRoutes(dac, out);
            // Remove all nodes after DAC, and make FFT the new OUT
            CollapseMap(dac, out);
            res *= CountRoutes(srv, out);
        }

        else {
            // FFT comes first, get routes from DAC to OUT
            res *= CountRoutes(dac, out);
            // Remove all nodes after DAC, and make DAC the new OUT
            CollapseMap(dac, out);
            // FFT now only required node
            res *= CountRoutes(fft, out);
            // Remove all nodes after FFT, and make FFT the new OUT
            CollapseMap(fft, out);
            res *= CountRoutes(srv, out);
        }
        return res;
    }

    std::uint64_t Day11::CountRoutes(int from, int to) {
        std::int64_t res = 0;
        std::stack<int> stack = {};
        stack.push(from);
        while (stack.size()) {
            auto current = stack.top(); stack.pop();
            if (current == to) { res++; continue; }
            for (auto& next : map[current]) {
                stack.push(next);
            }
        }
        return res;
    }

    std::unordered_set<int> Day11::NodesReachableFrom(int from) {
        std::stack<int> stack = {};
        std::unordered_set<int> seen = {};
        stack.push(from);
        while (stack.size()) {
            auto current = stack.top(); stack.pop();
            if (seen.contains(current)) { continue; }
            seen.insert(current);
            for (auto& next : map[current]) {
                stack.push(next);
            }
        }
        return seen;
    }

    void Day11::CollapseMap(int from, int newFromLabel) {
        auto nodesToRemove = NodesReachableFrom(from);
        nodesToRemove.erase(from);
        for (auto& node : nodesToRemove) {
            map.erase(node);
        }
        for (auto& route : map) {
            for (auto& node : nodesToRemove) {
                route.second.erase(node);
            }
        }
        for (auto& route : map) {
            if (route.second.contains(from)) {
                route.second.insert(newFromLabel);
                route.second.erase(from);
            }
        }
        map.erase(from);
    }
}