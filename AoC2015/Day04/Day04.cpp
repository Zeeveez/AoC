#include "Day04.h"

#include "../../Helpers/Helpers.h"
#include "../../AoC/MD5/MD5.h"

namespace AoC2015 {
    void Day04::Load() {
        input = AoC::Helpers::ReadToken<std::string>("./Day04.txt");
    }

    void Day04::Parse() {
        // No parsing required
    }

    void Day04::A() {
        partAResult.first = Test(input, [](std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> t) { return (std::get<0>(t) & 0x00000FFF) == std::get<0>(t); });
    }

    void Day04::B() {
        partBResult.first = Test(input, [](std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> t) { return (std::get<0>(t) & 0x000000FF) == std::get<0>(t); });
    }

    uint64_t Day04::Test(std::string input, std::function<bool(std::tuple<uint32_t, uint32_t, uint32_t, uint32_t>)> validityCheck) {
        int i = 0;
        while (true) {
            auto testInput = input + std::to_string(++i);
            if (validityCheck(AoC::MD5::Hash(testInput))) { return i; }
        }
    }
}