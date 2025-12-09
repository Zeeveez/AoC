#include <algorithm>
#include <numeric>

#include "Day01.h"

#include "../../Helpers/Helpers.h"

namespace AoC2015 {
    void Day01::Load() {
        input = AoC::Helpers::ReadToken<std::string>("./Day01.txt");
    }

    void Day01::Parse() {
        // No parsing required
    }

    void Day01::A() {
        int64_t res = 0;
        for (auto& c : input) {
            res += c == '(' ? 1 : -1;
        }

        partAResult.first = res;
    }

    void Day01::B() {
        int64_t n = 0;
        uint64_t res = 0;
        for (auto& c : input) {
            res++;
            n += c == '(' ? 1 : -1;
            if (n < 0) { break; }
        }

        partBResult.first = res;
    }
}