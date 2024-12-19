#ifndef DAY19_H
#define DAY19_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <map>

namespace AoC2024 {
    namespace Day19 {
        std::pair<std::vector<std::string>, std::vector<std::string>> PreProcessInput(const std::vector<std::string>& input);
        std::string Trim(const std::string& str);
        bool IsValid(const std::vector<std::string>& patterns, const std::string design);
        uint64_t CountValid(const std::vector<std::string>& patterns, std::map<std::string, uint64_t>& memory, const std::string design);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif