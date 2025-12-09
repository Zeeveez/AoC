#include "Day05.h"

#include "../../Helpers/Helpers.h"

namespace AoC2015 {
    void Day05::Load() {
        input = AoC::Helpers::ReadLines("./Day05.txt");
    }

    void Day05::Parse() {
        // No parsing required
    }

    void Day05::A() {
        uint64_t res = 0;
        for (auto& s : input) {
            res += VowelTest(s) && DoubleTest(s) && BadPairTest(s);
        }

        partAResult.first = res;
    }

    void Day05::B() {
        uint64_t res = 0;
        for (auto& s : input) {
            res += DoublePairTest(s) && DoubleGapTest(s);
        }

        partBResult.first = res;
    }

    inline bool Day05::VowelTest(const std::string& s) {
        int v = 0;
        for (auto& c : s) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                v++;
                if (v == 3) {
                    return true;
                }
            }
        }
        return false;
    }

    inline bool Day05::DoubleTest(const std::string& s) {
        for (int i = 0; i < s.length() - 1; i++) {
            if (s[i] == s[i + 1]) {
                return true;
            }
        }
        return false;
    }

    inline bool Day05::BadPairTest(const std::string& s) {
        for (int i = 0; i < s.length() - 1; i++) {
            if (s[i] == 'a' || s[i] == 'c' || s[i] == 'p' || s[i] == 'x') {
                if ((s[i] + 1) == s[i + 1]) {
                    return false;
                }
            }
        }
        return true;
    }

    inline bool Day05::DoublePairTest(const std::string& s) {
        for (int i = 0; i < s.length() - 3; i++) {
            for (int j = i + 2; j < s.length() - 1; j++) {
                if (s[i] == s[j] && s[i + 1] == s[j + 1]) {
                    return true;
                }
            }
        }
        return false;
    }

    inline bool Day05::DoubleGapTest(const std::string& s) {
        for (int i = 0; i < s.length() - 2; i++) {
            if (s[i] == s[i + 2]) {
                return true;
            }
        }
        return false;
    }
}