#ifndef DAY19_H
#define DAY19_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <set>

namespace AoC2022 {
    namespace Day19 {
        class Blueprint {
        public:
            int ID = 0;
            int oreBotCost = 0;
            int clayBotCost = 0;
            std::pair<int, int> obsidianBotCost = { 0, 0 };
            std::pair<int, int> geodeBotCost = { 0, 0 };

            int maxOreCost = 0;

            Blueprint() {};
            Blueprint(const std::string& input);
        };

        struct SimState {
        public:
            int ore = 0;
            int clay = 0;
            int obsidian = 0;
            int geodes = 0;
            int oreBots = 1;
            int clayBots = 0;
            int obsidianBots = 0;
            int geodeBots = 0;
            int time = 0;

            int MaxGeodes(int ticks) const;
            void Mine();
        };

        //template<>
        //std::hash<SimState>
        //{
        //    std::size_t operator()(const Pair& pair) const noexcept
        //    {
        //        std::size_t rtrn = static_cast<std::size_t>(pair.intval);
        //        rtrn = (rtrn << pair.bits.size()) | pair.bits.to_ulong();
        //        return rtrn;
        //    }
        //};

        class Simulation {
        public:
            std::vector<SimState> simStates = { SimState() };
            Blueprint* blueprint;

            Simulation(Blueprint* blueprint);

            int GetQuality();
            int GetGeodes();

            void PruneByGeodes(int ticks);
            
            int Run(int ticks, bool useQuality = true);
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif