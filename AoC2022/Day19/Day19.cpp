#include "Day19.h"

#include <regex>
#include <algorithm>

#include <iostream>

namespace AoC2022 {
    namespace Day19 {
        Blueprint::Blueprint(const std::string& input) {
            const std::regex cubeRe("[^\\d]+(\\d+)[^\\d]+(\\d+)[^\\d]+(\\d+)[^\\d]+(\\d+)[^\\d]+(\\d+)[^\\d]+(\\d+)[^\\d]+(\\d+)[^\\d]+");
            std::smatch sm;
            std::regex_search(input, sm, cubeRe);
            ID = std::stoi(sm[1]);
            oreBotCost = std::stoi(sm[2]);
            clayBotCost = std::stoi(sm[3]);
            obsidianBotCost = { std::stoi(sm[4]), std::stoi(sm[5]) };
            geodeBotCost = { std::stoi(sm[6]), std::stoi(sm[7]) };
            maxOreCost = std::max(std::max(oreBotCost, clayBotCost), std::max(obsidianBotCost.first, geodeBotCost.first));
        }

        int SimState::MaxGeodes(int ticks) const {
            int timeLeft = (ticks - time);
            return geodes + geodeBots * timeLeft + timeLeft * (timeLeft + 1) / 2;
        }

        void SimState::Mine() {
            ore += oreBots;
            clay += clayBots;
            obsidian += obsidianBots;
            geodes += geodeBots;
        }

        Simulation::Simulation(Blueprint* blueprint) {
            this->blueprint = blueprint;
        }

        int Simulation::GetQuality() {
            int maxQuality = 0;
            for (const auto& simState : simStates) {
                maxQuality = std::max(maxQuality, blueprint->ID * simState.geodes);
            }
            return maxQuality;
        }

        int Simulation::GetGeodes() {
            int maxQuality = 0;
            for (const auto& simState : simStates) {
                maxQuality = std::max(maxQuality, simState.geodes);
            }
            return maxQuality;
        }

        void Simulation::PruneByGeodes(int ticks) {
            int minMaxGeodes = 0;
            for (const auto& simState : simStates) {
                minMaxGeodes = std::max(minMaxGeodes, simState.MaxGeodes(ticks));
            }
            simStates.erase(std::remove_if(simStates.begin(), simStates.end(), [minMaxGeodes, ticks](const SimState& ss) { return ss.MaxGeodes(ticks) < minMaxGeodes; }), simStates.end());
        }

        int Simulation::Run(int ticks, bool useQuality) {
            for (int i = 0; i < ticks; i++) {
                std::vector<SimState> newSims = {};
                for (auto& sim : simStates) {
                    newSims.push_back(sim);
                    newSims[newSims.size() - 1].time++;
                    newSims[newSims.size() - 1].Mine();
                    if (sim.oreBots < blueprint->maxOreCost && sim.ore >= blueprint->oreBotCost) {
                        newSims.push_back(sim);
                        newSims[newSims.size() - 1].ore -= blueprint->oreBotCost;
                        newSims[newSims.size() - 1].time++;
                        newSims[newSims.size() - 1].Mine();
                        newSims[newSims.size() - 1].oreBots++;
                    }
                    if (sim.clayBots < blueprint->obsidianBotCost.second && sim.ore >= blueprint->clayBotCost) {
                        newSims.push_back(sim);
                        newSims[newSims.size() - 1].ore -= blueprint->clayBotCost;
                        newSims[newSims.size() - 1].time++;
                        newSims[newSims.size() - 1].Mine();
                        newSims[newSims.size() - 1].clayBots++;
                    }
                    if (sim.obsidianBots < blueprint->geodeBotCost.second && sim.ore >= blueprint->obsidianBotCost.first && sim.clay >= blueprint->obsidianBotCost.second) {
                        newSims.push_back(sim);
                        newSims[newSims.size() - 1].ore -= blueprint->obsidianBotCost.first;
                        newSims[newSims.size() - 1].clay -= blueprint->obsidianBotCost.second;
                        newSims[newSims.size() - 1].time++;
                        newSims[newSims.size() - 1].Mine();
                        newSims[newSims.size() - 1].obsidianBots++;
                    }
                    if (sim.ore >= blueprint->geodeBotCost.first && sim.obsidian >= blueprint->geodeBotCost.second) {
                        newSims.push_back(sim);
                        newSims[newSims.size() - 1].ore -= blueprint->geodeBotCost.first;
                        newSims[newSims.size() - 1].obsidian -= blueprint->geodeBotCost.second;
                        newSims[newSims.size() - 1].time++;
                        newSims[newSims.size() - 1].Mine();
                        newSims[newSims.size() - 1].geodeBots++;
                    }
                }
                simStates = newSims;
                newSims.clear();
                PruneByGeodes(ticks);
            }

            if (useQuality) {
                return GetQuality();
            }
            else {
                return GetGeodes();
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int score = 0;
            for (auto& line : input) {
                Blueprint bp = Blueprint(line);
                Simulation sim = Simulation(&bp);
                score += sim.Run(24);
                sim = Simulation(&bp);
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            int score = 1;
            for (int i = 0; i < std::min((size_t)3, input.size()); i++) {
                Blueprint bp = Blueprint(input[i]);
                Simulation sim = Simulation(&bp);
                int geodes = sim.Run(32, false);
                score *= geodes;
                std::cout << "Geodes: " << geodes << "\n";
                sim = Simulation(&bp);
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { score, endtime - starttime };
        }
    }
}