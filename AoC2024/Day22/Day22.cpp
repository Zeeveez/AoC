#include "Day22.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day22::Load() {
        input = AoC::Helpers::ReadLines("./Day22.txt");
    }

    void Day22::Parse() {
        // No parsing required
    }

    void Day22::A() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endtime - starttime };
    }

    void Day22::B() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endtime - starttime };
    }
}