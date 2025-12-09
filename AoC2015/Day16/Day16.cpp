#include "Day16.h"

#include <sstream>
#include <unordered_map>
#include <limits>
#include <algorithm>

namespace AoC2015 {
    namespace Day16 {
        std::string Packet::HexToBin(const std::string& hex) {
            const std::unordered_map<char, std::string> mapping = {
                { '0', "0000" }, { '1', "0001" }, { '2', "0010" }, { '3', "0011" },
                { '4', "0100" }, { '5', "0101" }, { '6', "0110" }, { '7', "0111" },
                { '8', "1000" }, { '9', "1001" }, { 'A', "1010" }, { 'B', "1011" },
                { 'C', "1100" }, { 'D', "1101" }, { 'E', "1110" }, { 'F', "1111" }
            };

            std::stringstream bin;
            for (auto& c : hex) {
                bin << mapping.at(c);
            }
            return bin.str();
        }

        uint64_t Packet::LoadBitsToInt(const std::string& bin, size_t& i, int n) {
            uint64_t v = 0;
            for (size_t j = 0; j < n; j++, i++) {
                v <<= 1;
                v += (bin[i] - '0');
            }
            return v;
        }

        uint64_t Packet::LoadPacketVersion(const std::string& bin, size_t& i) {
            return LoadBitsToInt(bin, i, 3);
        }

        uint64_t Packet::LoadPacketType(const std::string& bin, size_t& i) {
            return LoadBitsToInt(bin, i, 3);
        }

        uint64_t Packet::LoadLengthType(const std::string& bin, size_t& i) {
            return LoadBitsToInt(bin, i, 1);
        }

        uint64_t Packet::LoadLength(const std::string& bin, size_t& i) {
            return LoadBitsToInt(bin, i, 15);
        }

        uint64_t Packet::LoadSubPacketCount(const std::string& bin, size_t& i) {
            return LoadBitsToInt(bin, i, 11);
        }

        uint64_t Packet::LoadLiteral(const std::string& bin, size_t& i) {
            uint64_t v = 0;
            bool lastGroup;
            do {
                v <<= 4;
                lastGroup = bin[i++] == '0';
                v += LoadBitsToInt(bin, i, 4);
            } while (!lastGroup);
            return v;
        }

        void Packet::LoadPacket(const std::string& bin, size_t& i) {
            version = LoadPacketVersion(bin, i);
            type = LoadPacketType(bin, i);
            switch (type) {
            case 4:
                value = LoadLiteral(bin, i);
                break;
            default:
                lengthType = LoadLengthType(bin, i);
                switch (lengthType) {
                case 0:
                {
                    length = LoadLength(bin, i);
                    int currentIndex = i;
                    do {
                        subPackets.push_back(Packet(bin, i));
                    } while (i < currentIndex + length);
                    break;
                }
                case 1:
                    length = LoadSubPacketCount(bin, i);
                    for (int j = 0; j < length; j++) {
                        subPackets.push_back(Packet(bin, i));
                    }
                }
            }
        }

        Packet::Packet(const std::string& hex) {
            auto bin = HexToBin(hex);
            size_t i = 0;
            LoadPacket(bin, i);
        }

        Packet::Packet(const std::string& bin, size_t& i) {
            LoadPacket(bin, i);
        }

        uint64_t Packet::GetVersionSum() {
            uint64_t s = version;
            for (auto& sub : subPackets) {
                s += sub.GetVersionSum();
            }
            return s;
        }

        uint64_t Packet::CalculateResult() {
            uint64_t v = 0;
            switch (type) {
            case 0:
            {
                v = 0;
                for (auto& sub : subPackets) {
                    v += sub.CalculateResult();
                }
                break;
            }
            case 1:
            {
                v = 1;
                for (auto& sub : subPackets) {
                    v *= sub.CalculateResult();
                }
                break;
            }
            case 2:
            {
                v = std::numeric_limits<uint64_t>::max();
                for (auto& sub : subPackets) {
                    v = std::min(v, sub.CalculateResult());
                }
                break;
            }
            case 3:
            {
                v = std::numeric_limits<uint64_t>::min();
                for (auto& sub : subPackets) {
                    v = std::max(v, sub.CalculateResult());
                }
                break;
            }
            case 4:
            {
                v = value;
                break;
            }
            case 5:
            {
                v = subPackets[0].CalculateResult() > subPackets[1].CalculateResult() ? 1 : 0;
                break;
            }
            case 6:
            {
                v = subPackets[0].CalculateResult() < subPackets[1].CalculateResult() ? 1 : 0;
                break;
            }
            case 7:
            {
                v = subPackets[0].CalculateResult() == subPackets[1].CalculateResult() ? 1 : 0;
                break;
            }
            }
            return v;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::string& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            Packet packet(input);
            uint64_t res = packet.GetVersionSum();
            auto endTime = std::chrono::high_resolution_clock::now();
            return { res, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::string& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            Packet packet(input);
            uint64_t res = packet.CalculateResult();
            auto endTime = std::chrono::high_resolution_clock::now();
            return { res, endTime - startTime };
        }
    }
}