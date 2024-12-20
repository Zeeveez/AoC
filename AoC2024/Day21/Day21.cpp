#include "Day21.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day21::Load() {
        input = AoC::Helpers::ReadLines("./Day21.txt");
    }

    void Day21::Parse() {
        // No parsing required
    }

    void Day21::A() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endtime - starttime };
    }

    void Day21::B() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endtime - starttime };
    }
}