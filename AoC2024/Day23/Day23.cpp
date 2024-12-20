#include "Day23.h"
#include "../../Helpers/Helpers.h"

namespace AoC2024 {
    void Day23::Load() {
        input = AoC::Helpers::ReadLines("./Day23.txt");
    }

    void Day23::Parse() {
        // No parsing required
    }

    void Day23::A() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endtime - starttime };
    }

    void Day23::B() {
        auto starttime = std::chrono::high_resolution_clock::now();

        uint64_t res = -1;

        auto endtime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endtime - starttime };
    }
}