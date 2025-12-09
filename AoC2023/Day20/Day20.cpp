#include "Day20.h"

#include <iostream>
#include <regex>
#include <numeric>

namespace AoC2023::Day20 {
    Module::Module(const std::string& mdl) {
        if (mdl[0] == '%' || mdl[0] == '&') {
            type = mdl[0];
            name = mdl.substr(1, mdl.find(' ') - 1);
            state = false;

            std::string::const_iterator outputSearch(mdl.cbegin() + mdl.find('>'));
            static const std::regex outputRe("([a-z]+)", std::regex::optimize);
            std::smatch outputMatch;
            while (std::regex_search(outputSearch, mdl.cend(), outputMatch, outputRe)) {
                targets.push_back(outputMatch[1].str());
                outputSearch = outputMatch.suffix().first;
            }
        }
        else {
            type = '\0';
            name = mdl.substr(0, mdl.find(' '));

            std::string::const_iterator outputSearch(mdl.cbegin() + mdl.find('>'));
            static const std::regex outputRe("([a-z]+)", std::regex::optimize);
            std::smatch outputMatch;
            while (std::regex_search(outputSearch, mdl.cend(), outputMatch, outputRe)) {
                targets.push_back(outputMatch[1].str());
                outputSearch = outputMatch.suffix().first;
            }
        }
    }

    void Module::Propagate(bool pulse, std::string src, std::queue<std::tuple<std::string, std::string, bool>>& pulseQueue) {
        if (type == '%') {
            if (!pulse) {
                state = !state;
                for (auto& target : targets) {
                    pulseQueue.push({ target, name, state });
                }
            }
        }
        else if (type == '&') {
            inputs[src] = pulse;
            for (auto& input : inputs) {
                if (!input.second) {
                    for (auto& target : targets) {
                        pulseQueue.push({ target, name, true });
                    }
                    return;
                }
            }
            for (auto& target : targets) {
                pulseQueue.push({ target, name, false });
            }
            return;
        }
        else {
            for (auto& target : targets) {
                pulseQueue.push({ target, name, pulse });
            }
        }
    }

    std::map<std::string, Module> ParseInput(const std::vector<std::string>& input) {
        std::map<std::string, Module> modules = {};
        for (auto& line : input) {
            Module mdl = Module(line);
            modules[mdl.name] = mdl;
        }

        for (auto& module : modules) {
            for (auto& target : module.second.targets) {
                modules[target].inputs[module.second.name] = false;
            }
        }
        return modules;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto modules = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t highs = 0;
        uint64_t lows = 0;
        std::queue<std::tuple<std::string, std::string, bool>> pulseQueue;

        for (size_t i = 0; i < 1000; i++) {
            pulseQueue.push({ "broadcaster", "button", false });
            while (!pulseQueue.empty()) {
                auto pulse = pulseQueue.front(); pulseQueue.pop();
                highs += std::get<2>(pulse) ? 1 : 0;
                lows += std::get<2>(pulse) ? 0 : 1;
                modules[std::get<0>(pulse)].Propagate(std::get<2>(pulse), std::get<1>(pulse), pulseQueue);
            }
        }

        int64_t score = highs * lows;

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto modules = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t highs = 0;
        uint64_t lows = 0;
        std::queue<std::tuple<std::string, std::string, bool>> pulseQueue;

        int dhHighFirst = -1;
        int dhHighSecond = -1;
        int mkHighFirst = -1;
        int mkHighSecond = -1;
        int vfHighFirst = -1;
        int vfHighSecond = -1;
        int rnHighFirst = -1;
        int rnHighSecond = -1;

        size_t i = 0;
        while (true) {
            i++;
            pulseQueue.push({ "broadcaster", "button", false });
            while (!pulseQueue.empty()) {
                auto pulse = pulseQueue.front(); pulseQueue.pop();
                if (std::get<1>(pulse) == "dh" && std::get<2>(pulse)) {
                    if (dhHighFirst < 0) { dhHighFirst = i; }
                    else if (dhHighSecond < 0 && dhHighFirst != i) { dhHighSecond = i; }
                }
                if (std::get<1>(pulse) == "mk" && std::get<2>(pulse)) {
                    if (mkHighFirst < 0) { mkHighFirst = i; }
                    else if (mkHighSecond < 0 && mkHighFirst != i) { mkHighSecond = i; }
                }
                if (std::get<1>(pulse) == "vf" && std::get<2>(pulse)) {
                    if (vfHighFirst < 0) { vfHighFirst = i; }
                    else if (vfHighSecond < 0 && vfHighFirst != i) { vfHighSecond = i; }
                }
                if (std::get<1>(pulse) == "rn" && std::get<2>(pulse)) {
                    if (rnHighFirst < 0) { rnHighFirst = i; }
                    else if (rnHighSecond < 0 && rnHighFirst != i) { rnHighSecond = i; }
                }
                if (dhHighSecond > 0 && mkHighSecond > 0 && vfHighSecond > 0 && rnHighSecond > 0) { goto done; }
                modules[std::get<0>(pulse)].Propagate(std::get<2>(pulse), std::get<1>(pulse), pulseQueue);
            }
        }
    done:;

        uint64_t dhRepeat = dhHighSecond - dhHighFirst;
        uint64_t mkRepeat = mkHighSecond - mkHighFirst;
        uint64_t vfRepeat = vfHighSecond - vfHighFirst;
        uint64_t rnRepeat = rnHighSecond - rnHighFirst;

        uint64_t totalRepeat = std::lcm(std::lcm(std::lcm(dhRepeat, mkRepeat), vfRepeat), rnRepeat);

        auto endTime = std::chrono::high_resolution_clock::now();
        return { totalRepeat, parseEnd - parseStart, endTime - startTime };
    }
}