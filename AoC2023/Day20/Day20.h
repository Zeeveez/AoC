#ifndef DAY20_H
#define DAY20_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <functional>
#include <map>
#include <queue>

namespace AoC2023::Day20 {
    enum RatingType {
        ExtremelyCoolLooking,
        Musical,
        Aerodynamic,
        Shiny
    };

    class Module {
    public:
        char type;
        std::string name;
        std::vector<std::string> targets;
        std::map<std::string, bool> inputs;
        bool state;

        Module() = default;
        Module(const std::string& mdl);
        void Propagate(bool pulse, std::string src, std::queue<std::tuple<std::string, std::string, bool>>& pulseQueue);
    };

    std::map<std::string, Module> ParseInput(const std::vector<std::string>& input);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif