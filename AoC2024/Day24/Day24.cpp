#include "Day24.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day24::Load() {
        input = AoC::Helpers::ReadLines("./Day24.txt");
    }

    void Day24::Parse() {
        // No parsing required
    }

    void Day24::A() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endtime - starttime };
    }

    void Day24::B() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endtime - starttime };
    }
}