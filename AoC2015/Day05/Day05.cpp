#include "Day05.h"

namespace AoC2015 {
    namespace Day05 {
        inline bool VowelTest(const std::string& s) {
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

        inline bool DoubleTest(const std::string& s) {
            for (int i = 0; i < s.length() - 1; i++) {
                if (s[i] == s[i + 1]) {
                    return true;
                }
            }
            return false;
        }

        inline bool BadPairTest(const std::string& s) {
            for (int i = 0; i < s.length() - 1; i++) {
                if (s[i] == 'a' || s[i] == 'c' || s[i] == 'p' || s[i] == 'x') {
                    if ((s[i] + 1) == s[i + 1]) {
                        return false;
                    }
                }
            }
            return true;
        }

        inline bool DoublePairTest(const std::string& s) {
            for (int i = 0; i < s.length() - 3; i++) {
                for (int j = i + 2; j < s.length() - 1; j++) {
                    if (s[i] == s[j] && s[i + 1] == s[j + 1]) {
                        return true;
                    }
                }
            }
            return false;
        }

        inline bool DoubleGapTest(const std::string& s) {
            for (int i = 0; i < s.length() - 2; i++) {
                if (s[i] == s[i + 2]) {
                    return true;
                }
            }
            return false;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            int c = 0;
            for (auto& s : input) {
                c += VowelTest(s) && DoubleTest(s) && BadPairTest(s);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            int c = 0;
            for (auto& s : input) {
                c += DoublePairTest(s) && DoubleGapTest(s);
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { c, endTime - startTime };
        }
    }
}