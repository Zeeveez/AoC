#pragma once
#include <vector>
#include <string>
#include <cstdint>

#include "../../Shared/Day/Day.h"

namespace AoC2025 {
    class Day10 : public AoC::Day<std::vector<std::string>, 2025, 10> {
    private:
        class Machine {
        public:
            std::uint64_t requiredLights;
            std::vector<std::uint64_t> buttonValues;
            std::vector<std::vector<int>> buttonMappings;
            std::vector<int> voltages;

            std::string line;

            Machine(std::string& line);
            void ParseLights(std::string& line, int& i);
            void ParseButtons(std::string& line, int& i);
            void ParseVoltages(std::string& line, int& i);

            int CountRequiredLightButtons();
            void CountRequiredLightButtons(std::uint64_t currentLights, int& best, int runningTotal = 0, int index = 0);
            int CountRequiredVoltageButtons();
            void CountRequiredVoltageButtons(std::vector<int>& currentVoltages, int& best, int runningTotal, int index);
        };

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        std::vector<Machine> machines;
    };
}