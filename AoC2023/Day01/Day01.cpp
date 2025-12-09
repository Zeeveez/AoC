#include <cstring>

#include "Day01.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day01::Load() {
        input = AoC::Helpers::ReadLines("./Day01.txt");
    }

    void Day01::Parse() {
        // No parsing required
    }

    void Day01::A() {
        uint64_t res = 0;
        for (auto& l : input) {
            auto digits = GetDigits(l);
            res += digits[0] * 10 + digits[digits.size() - 1];
        }
        partAResult.first = res;
    }

    void Day01::B() {
        uint64_t res = 0;
        for (auto& l : input) {
            auto digits = GetDigits(l, true);
            res += digits[0] * 10 + digits[digits.size() - 1];
        }
        partBResult.first = res;
    }

    std::vector<uint64_t> Day01::GetDigits(const std::string& input, bool includeWords) {
        std::vector<uint64_t> digits = {};

        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] >= '0' && input[i] <= '9') {
                digits.push_back(input[i] - '0');
                continue;
            }

            if (includeWords) {
                if (i < input.length() - 2 && std::memcmp(input.c_str() + i, "one", 3) == 0) { digits.push_back(1); }
                else if (i < input.length() - 2 && std::memcmp(input.c_str() + i, "two", 3) == 0) { digits.push_back(2);  }
                else if (i < input.length() - 4 && std::memcmp(input.c_str() + i, "three", 5) == 0) { digits.push_back(3);  }
                else if (i < input.length() - 3 && std::memcmp(input.c_str() + i, "four", 4) == 0) { digits.push_back(4);  }
                else if (i < input.length() - 3 && std::memcmp(input.c_str() + i, "five", 4) == 0) { digits.push_back(5);  }
                else if (i < input.length() - 2 && std::memcmp(input.c_str() + i, "six", 3) == 0) { digits.push_back(6);  }
                else if (i < input.length() - 4 && std::memcmp(input.c_str() + i, "seven", 5) == 0) { digits.push_back(7);  }
                else if (i < input.length() - 4 && std::memcmp(input.c_str() + i, "eight", 5) == 0) { digits.push_back(8);  }
                else if (i < input.length() - 3 && std::memcmp(input.c_str() + i, "nine", 4) == 0) { digits.push_back(9);  }
            }
        }

        return digits;
    }
}