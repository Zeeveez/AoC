#include <vector>
#include <array>

#include "MD5.h"


// https://en.wikipedia.org/wiki/MD5
// https://rosettacode.org/wiki/MD5/Implementation_Debug
namespace AoC {
    const uint32_t MD5::s[] = {
                7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    };
    const uint32_t MD5::K[] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
            0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
            0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
            0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
            0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
            0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
            0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
            0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    std::tuple<uint32_t, uint32_t, uint32_t, uint32_t> MD5::Hash(std::string input) {
        std::vector<unsigned char> data(input.begin(), input.end());
        data.reserve((data.size() / 64 + 1) * 64);

        uint64_t dataSize = data.size() * 8;
        data.push_back(0b10000000);
        while (data.size() % 64 != 56) { data.push_back(0); }
        for (size_t i = 0; i < 8; i++) {
            unsigned char dataSizeByte = (dataSize >> (8 * i)) & 0xFF;
            data.push_back(dataSizeByte);
        }

        uint32_t a0 = a0init;
        uint32_t b0 = b0init;
        uint32_t c0 = c0init;
        uint32_t d0 = d0init;

        for (size_t i = 0; i < data.size(); i += 64) {
            std::array<uint32_t, 16> M;
            for (int j = 0; j < 16; j++) {
                M[j] = (data[i + j * 4 + 3] << 24) | (data[i + j * 4 + 2] << 16) | (data[i + j * 4 + 1] << 8) | (data[i + j * 4 + 0] << 0);
            }
            uint32_t A = a0;
            uint32_t B = b0;
            uint32_t C = c0;
            uint32_t D = d0;

            for (size_t j = 0; j < 64; j++) {
                uint32_t F = 0;
                uint32_t g = 0;

                if (j < 16) {
                    F = (B & C) | ((~B) & D);
                    g = j;
                }
                else if (j < 32) {
                    F = (D & B) | ((~D) & C);
                    g = (5 * j + 1) % 16;
                }
                else if (j < 48) {
                    F = B ^ C ^ D;
                    g = (3 * j + 5) % 16;
                }
                else {
                    F = C ^ (B | (~D));
                    g = (7 * j) % 16;
                }

                F += A + K[j] + M[g];
                A = D;
                D = C;
                C = B;
                B += (F << s[j]) | (F >> (32 - s[j]));
            }

            a0 += A;
            b0 += B;
            c0 += C;
            d0 += D;
        }

        uint32_t littleEndianA = (((a0 >> 24) & 0xFF) << 0) | (((a0 >> 16) & 0xFF) << 8) | (((a0 >> 8) & 0xFF) << 16) | (((a0 >> 0) & 0xFF) << 24);
        uint32_t littleEndianB = (((b0 >> 24) & 0xFF) << 0) | (((b0 >> 16) & 0xFF) << 8) | (((b0 >> 8) & 0xFF) << 16) | (((b0 >> 0) & 0xFF) << 24);
        uint32_t littleEndianC = (((c0 >> 24) & 0xFF) << 0) | (((c0 >> 16) & 0xFF) << 8) | (((c0 >> 8) & 0xFF) << 16) | (((c0 >> 0) & 0xFF) << 24);
        uint32_t littleEndianD = (((d0 >> 24) & 0xFF) << 0) | (((d0 >> 16) & 0xFF) << 8) | (((d0 >> 8) & 0xFF) << 16) | (((d0 >> 0) & 0xFF) << 24);
        return { littleEndianA, littleEndianB, littleEndianC, littleEndianD };
    }
}