#pragma once

#include <tuple>
#include <cstdint>
#include <string>

namespace AoC {
    class MD5 {
    public:
        static std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> Hash(std::string input);

    private:
        static const uint32_t s[64];
        static const uint32_t K[64];
        static const uint32_t a0init = 0x67452301;
        static const uint32_t b0init = 0xefcdab89;
        static const uint32_t c0init = 0x98badcfe;
        static const uint32_t d0init = 0x10325476;
    };
}