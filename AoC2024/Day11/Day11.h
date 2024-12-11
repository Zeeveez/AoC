#ifndef DAY11_H
#define DAY11_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2024 {
    namespace Day11 {
        class Stone {
        public:
            uint64_t value;
            uint64_t count;
            Stone() = default;
            Stone(uint64_t value, uint64_t count);
            std::optional<Stone> Iterate();
        };
        uint64_t Run(const std::vector<uint64_t>& input, int iterations);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<uint64_t>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<uint64_t>& input);
    }
}
#endif