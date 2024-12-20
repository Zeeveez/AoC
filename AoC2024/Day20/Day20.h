#ifndef DAY20_H
#define DAY20_H

#include "../Day/Day.h"

#include <vector>
#include <string>

namespace AoC2024 {
    class Day20 : public AoC::Day {
    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day20() : Day() {
            Load();
            Parse();
            A();
            B();
        }

    private:
        std::vector<std::string> input = {};
        std::pair<int, int> FindEnd(const std::vector<std::string>& input);

        uint64_t CountPaths(const std::vector<std::string>& input, std::vector<int>& distancesToEnd, int maxCheatLength, int minTimeSave);
        std::vector<int> GetDistancesFromPoint(const std::vector<std::string>& input, int x, int y);
        uint64_t Run(const std::vector<std::string>& input, int maxCheatLength);
    };
}
#endif