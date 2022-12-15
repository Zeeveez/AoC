#include "Day12.h"

#include <algorithm>
#include <cctype>

namespace AoC2015 {
    namespace Day12 {
        std::pair<std::unordered_map<char, int>, std::unordered_map<char, std::vector<char>>> PreProcessInput(const std::vector<std::string>& input) {
            std::unordered_map<char, int> visitedNodes = {};
            std::unordered_map<char, std::vector<char>> output = {};
            for (auto& line : input) {
                char start = line[0];
                char end = line[line.find('-') + 1];
                if (end != 's') {
                    if (!output.contains(start)) {
                        visitedNodes[start] = 0;
                        output[start] = { end };
                    }
                    else if (std::find(output[start].begin(), output[start].end(), end) == output[start].end()) {
                        output[start].push_back(end);
                    }
                }
                if (start != 's') {
                    if (!output.contains(end)) {
                        visitedNodes[end] = 0;
                        output[end] = { start };
                    }
                    else if (std::find(output[end].begin(), output[end].end(), start) == output[end].end()) {
                        output[end].push_back(start);
                    }
                }
            }
            return { visitedNodes, output };
        }

        void TraverseAllPaths(const std::unordered_map<char, std::vector<char>>& map,
                                uint64_t& paths,
                                std::unordered_map<char, int>& visitedNodes,
                                bool haveDouble,
                                char nextNode)
        {
            if (nextNode == 'e') {
                paths++;
                return;
            }
            if (nextNode <= 'Z' || !visitedNodes.at(nextNode)) {
                visitedNodes[nextNode]++;
                for (auto& possiblePath : map.at(nextNode)) {
                    TraverseAllPaths(map, paths, visitedNodes, haveDouble, possiblePath);
                }
                visitedNodes[nextNode]--;
                return;
            }
            if (haveDouble) {
                visitedNodes[nextNode]++;
                for (auto& possiblePath : map.at(nextNode)) {
                    TraverseAllPaths(map, paths, visitedNodes, false, possiblePath);
                }
                visitedNodes[nextNode]--;
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> Run(const std::vector<std::string>& input, bool haveDouble) {
            auto startTime = std::chrono::high_resolution_clock::now();
                auto [visitedNodes, map] = PreProcessInput(input);
                uint64_t paths = 0;
                TraverseAllPaths(map, paths, visitedNodes, haveDouble);
                auto endTime = std::chrono::high_resolution_clock::now();
                return { paths, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            return Run(input);
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            return Run(input, true);
        }
    }
}

//#include "Day12.h"
//
//#include <algorithm>
//#include <cctype>
//
//namespace AoC2015 {
//    namespace Day12 {
//        std::unordered_map<std::string, std::vector<std::string>> PreProcessInput(const std::vector<std::string>& input) {
//            std::unordered_map<std::string, std::vector<std::string>> output = {};
//            for (auto& line : input) {
//                std::string start = line.substr(0, line.find('-'));
//                std::string end = line.substr(line.find('-') + 1);
//                if (!output.contains(start)) {
//                    output[start] = { end };
//                }
//                else if (std::find(output[start].begin(), output[start].end(), end) == output[start].end()) {
//                    output[start].push_back(end);
//                }
//                if (!output.contains(end)) {
//                    output[end] = { start };
//                }
//                else if (std::find(output[end].begin(), output[end].end(), start) == output[end].end()) {
//                    output[end].push_back(start);
//                }
//            }
//            return output;
//        }
//
//        void TraverseAllPaths(const std::unordered_map<std::string, std::vector<std::string>>& map,
//                              std::vector<std::vector<std::string>>& paths,
//                              std::function<bool(const std::vector<std::string>&, const std::string&, bool& haveDouble)> pathingRule,
//                              std::vector<std::string>& currentPath,
//                              bool haveDouble,
//                              std::string nextNode,
//                              std::string endNode)
//        {
//            if (nextNode == endNode) {
//                paths.push_back(currentPath);
//                return;
//            }
//            if (!pathingRule(currentPath, nextNode, haveDouble)) {
//                return;
//            }
//            currentPath.push_back(nextNode);
//            for (auto& possiblePath : map.at(nextNode)) {
//                TraverseAllPaths(map, paths, pathingRule, currentPath, haveDouble, possiblePath, endNode);
//            }
//            currentPath.pop_back();
//        }
//
//        std::vector<std::vector<std::string>> TraverseAllPaths(const std::unordered_map<std::string, std::vector<std::string>>& map,
//                                                               std::function<bool(const std::vector<std::string>&, const std::string&, bool& haveDouble)> pathingRule,
//                                                               bool haveDouble,
//                                                               std::string nextNode,
//                                                               std::string endNode) {
//            std::vector<std::vector<std::string>> paths = {};
//            std::vector<std::string> currentPath = {};
//            TraverseAllPaths(map, paths, pathingRule, currentPath, haveDouble);
//            return paths;
//        }
//
//        bool PathingRule(const std::vector<std::string>& currentPath, const std::string& nextNode, bool& haveDouble) {
//            if (std::isupper(nextNode[0]) || currentPath.size() == 0) { return true; }
//            if (nextNode == currentPath[0]) { return false; }
//            if (std::find(currentPath.begin(), currentPath.end(), nextNode) == currentPath.end()) { return true; }
//            if (haveDouble) { haveDouble = false; return true; }
//            return false;
//        }
//
//        std::pair<uint64_t, std::chrono::duration<double, std::milli>> Run(const std::vector<std::string>& input, std::function<bool(const std::vector<std::string>&, const std::string&, bool& haveDouble)> pathingRule, bool haveDouble) {
//            auto startTime = std::chrono::high_resolution_clock::now();
//            auto map = PreProcessInput(input);
//            auto paths = TraverseAllPaths(map, pathingRule, haveDouble);
//            auto endTime = std::chrono::high_resolution_clock::now();
//            return { paths.size(), endTime - startTime };
//        }
//
//        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
//            return Run(input, PathingRule);
//        }
//
//        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
//            return Run(input, PathingRule, true);
//        }
//    }
//}