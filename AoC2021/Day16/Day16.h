#ifndef DAY16_H
#define DAY16_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2021 {
    namespace Day16 {
        struct Packet {
        public:
            // Shared
            uint64_t version = 0;
            uint64_t type = 0;

            // Literal
            uint64_t value = 0;

            // Operator
            uint64_t lengthType = 0;
            uint64_t length = 0;
            std::vector<Packet> subPackets = {};

        private:
            std::string HexToBin(const std::string& hex);
            uint64_t LoadBitsToInt(const std::string& bin, size_t& i, int n);
            uint64_t LoadPacketVersion(const std::string& bin, size_t& i);
            uint64_t LoadPacketType(const std::string& bin, size_t& i);
            uint64_t LoadLengthType(const std::string& bin, size_t& i);
            uint64_t LoadLength(const std::string& bin, size_t& i);
            uint64_t LoadSubPacketCount(const std::string& bin, size_t& i);
            uint64_t LoadLiteral(const std::string& bin, size_t& i);
            void LoadPacket(const std::string& bin, size_t& i);
            Packet(const std::string& hex, size_t& i);

        public:
            Packet(const std::string& hex);
            uint64_t GetVersionSum();
            uint64_t CalculateResult();
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input);
    }
}
#endif