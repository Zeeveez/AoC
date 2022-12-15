#ifndef DAY12_H
#define DAY12_H

#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <functional>


namespace AoC2015 {
    namespace Day12 {
        std::pair<std::unordered_map<char, int>, std::unordered_map<char, std::vector<char>>> PreProcessInput(const std::vector<std::string>& input);

        void TraverseAllPaths(const std::unordered_map<char, std::vector<char>>& map,
                              uint64_t& paths,
                              std::unordered_map<char, int>& visitedNodes,
                              bool haveDouble = false,
                              char nextNode = 's');

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> Run(const std::vector<std::string>& input, bool haveDouble = false);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif

//#ifndef DAY12_H
//#define DAY12_H
//
//#include <vector>
//#include <string>
//#include <unordered_map>
//#include <chrono>
//#include <functional>
//
//
//namespace AoC2015 {
//    namespace Day12 {
//        std::unordered_map<std::string, std::vector<std::string>> PreProcessInput(const std::vector<std::string>& input);
//
//        void TraverseAllPaths(const std::unordered_map<std::string, std::vector<std::string>>& map,
//                              std::vector<std::vector<std::string>>& paths,
//                              std::function<bool(const std::vector<std::string>&, const std::string&, bool& haveDouble)> pathingRule,
//                              std::vector<std::string>& currentPath,
//                              bool haveDouble = false,
//                              std::string nextNode = "start",
//                              std::string endNode = "end");
//
//        std::vector<std::vector<std::string>> TraverseAllPaths(const std::unordered_map<std::string, std::vector<std::string>>& map,
//                                                               std::function<bool(const std::vector<std::string>&, const std::string&, bool& haveDouble)> pathingRule,
//                                                               bool haveDouble = false,
//                                                               std::string nextNode = "start",
//                                                               std::string endNode = "end");
//
//        bool PathingRule(const std::vector<std::string>& currentPath, const std::string& nextNode, bool& haveDouble);
//
//        std::pair<uint64_t, std::chrono::duration<double, std::milli>> Run(const std::vector<std::string>& input, std::function<bool(const std::vector<std::string>&, const std::string&, bool& haveDouble)> pathingRule, bool haveDouble = false);
//
//        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
//        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
//    }
//}
//#endif