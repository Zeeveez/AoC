#ifndef DAY04_H
#define DAY04_H

#include <vector>
#include <string>
#include <chrono>
#include <functional>

namespace AoC2015 {
    namespace Day04 {
        std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> MD5(std::string);
        uint64_t Test(std::string, std::function<bool(std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>)> validityCheck);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input);
    }
}
#endif