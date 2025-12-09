#pragma once
#include <vector>
#include <string>
#include <tuple>

#include "../../Shared/Day/Day.h"

namespace AoC2019 {
    class Day04 : public AoC::Day<std::string, 2019, 4> {
    private:
        int passwordStart;
        int passwordEnd;

        void Parse() override;
        AoC::DayResult::PuzzleResult A() override;
        AoC::DayResult::PuzzleResult B() override;

        bool PasswordCheck(int password, bool (*)(int));
        int RunPasswords(int pwStart, int pwEnd, bool (*f)(int));
    };
}