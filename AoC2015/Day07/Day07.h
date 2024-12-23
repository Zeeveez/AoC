#pragma once
#include <variant>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../AoC/Day/Day.h"

namespace AoC2015 {
    class Day07 : public AoC::Day {
    private:
        class Part {
            enum class Operator {
                AND,
                OR,
                LSHIFT,
                RSHIFT,
                NOT,
                NONE
            };

            std::variant<std::uint16_t, Part*> input1 = static_cast<std::uint16_t>(0);
            std::variant<std::uint16_t, Part*> input2 = static_cast<std::uint16_t>(0);
            int inputPart1Id = -1;
            int inputPart2Id = -1;
            Operator type = Operator::NONE;
            bool evaluated = false;

        public:
            int id = -1;
            std::uint16_t output = 0;

            Part() = default;
            Part(std::string def);
            static std::size_t GetId(std::string label);
            void AssignInputs(std::unordered_map<int, Part>& parts);
            void CalculateOutput();
            std::vector<Part*> GetPreReqs() const;
        };

    public:
        void Load() override;
        void Parse() override;
        void A() override;
        void B() override;

        Day07() : Day() {
            dayNo = 7;
            Load();
            parseResult.second = TimeFunc([&]() { Parse(); });
            partAResult.second = TimeFunc([&]() { A(); });
            partBResult.second = TimeFunc([&]() { B(); });
        }

    private:
        std::vector<std::string> input = {};
        std::unordered_map<int, Part> parts = {};
    };
}