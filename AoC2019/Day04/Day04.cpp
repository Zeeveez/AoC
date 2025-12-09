#include <algorithm>
#include <numeric>

#include "Day04.h"

namespace AoC2019 {
    void Day04::Parse() {
        bool numFlag = false;
        for (auto& c : rawData) {
            if (c == '-') { numFlag = true; }
            else if (!numFlag) { passwordStart = passwordStart * 10 + c - '0'; }
            else { passwordEnd = passwordEnd * 10 + c - '0'; }
        }
    }

    AoC::DayResult::PuzzleResult Day04::A() {
        return RunPasswords(passwordStart, passwordEnd, [](int n) {return n >= 2; });
    }

    AoC::DayResult::PuzzleResult Day04::B() {
        return RunPasswords(passwordStart, passwordEnd, [](int n) {return n == 2; });
    }

    bool Day04::PasswordCheck(int _pw, bool (*f)(int)) {
        std::string pw = std::to_string(_pw);
        for (size_t i = 0; i < pw.length() - 1; i++) {
            if (pw[i + 1] < pw[i]) {
                return false;
            }
        }
        return std::any_of(pw.begin(), pw.end(), [pw, f](char c) { return f(std::count(pw.begin(), pw.end(), c)); });
    }

    int Day04::RunPasswords(int pwStart, int pwEnd, bool (*f)(int)) {
        std::vector<int> range(pwEnd - pwStart + 1);
        std::iota(range.begin(), range.end(), pwStart);
        return std::accumulate(range.begin(), range.end(), 0, [&](int acc, int pw) { return acc + (PasswordCheck(pw, f) ? 1 : 0); });
    }
}