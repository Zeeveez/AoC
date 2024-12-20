#include "Day25.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day25::Load() {
        input = AoC::Helpers::ReadLines("./Day25.txt");
    }

    void Day25::Parse() {
        // No parsing required
    }

    void Day25::A() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endtime - starttime };
    }

    void Day25::B() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endtime - starttime };
    }
}