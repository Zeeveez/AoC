#ifndef DAY18_H
#define DAY18_H

#include <vector>
#include <string>
#include <chrono>

namespace AoC2015 {
    namespace Day18 {
        struct Snailfish {
        public:
            // Shared
            bool isPair = false;

            // Value
            uint64_t value = 0;

            // Pair
            std::vector<Snailfish> pair = {};

        private:
            void LoadSnailfish(const std::string& input, size_t& i);
            bool CheckExplosions();
            std::pair<bool, uint64_t*> CheckExplosions(int depth, uint64_t*& lastRegularNumber);
            bool ApplyExplosionRight(uint64_t* value);
            bool CheckSplits();
            Snailfish(int64_t value);
            Snailfish(const std::string& input, size_t& i);

        public:
            Snailfish(Snailfish s1, Snailfish s2);
            Snailfish(const std::string& input);

            uint64_t CalculateMagnitude();
            void Reduce();
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif