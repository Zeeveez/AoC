#include "Day18.h"

#include <algorithm>

namespace AoC2015 {
    namespace Day18 {
        void Snailfish::LoadSnailfish(const std::string& input, size_t& i) {
            if (input[i] == '[') {
                i++; // skip opening bracket
                isPair = true;
                pair.clear();
                pair.push_back(Snailfish(input, i));
                i++; // skip comma
                pair.push_back(Snailfish(input, i));
                i++; // skip closing bracket
            }
            else {
                isPair = false;
                value = input[i++] - '0';
            }
        }

        bool Snailfish::CheckExplosions() {
            uint64_t* lastRegularNumber = nullptr;
            return CheckExplosions(0, lastRegularNumber).first;
        }

        std::pair<bool, uint64_t*> Snailfish::CheckExplosions(int depth, uint64_t*& lastRegularNumber) {
            if (isPair) {
                if (depth >= 4) {
                    if (lastRegularNumber != nullptr) {
                        (*lastRegularNumber) += pair[0].value;
                    }
                    isPair = false;
                    value = 0;
                    return { true, &pair[1].value };
                }
                else {
                    auto p1Check = pair[0].CheckExplosions(depth + 1, lastRegularNumber);
                    if (p1Check.first) {
                        pair[1].ApplyExplosionRight(p1Check.second);
                        return p1Check;
                    }
                    return pair[1].CheckExplosions(depth + 1, lastRegularNumber);
                }
            }
            lastRegularNumber = &value;
            return { false, nullptr };
        }

        bool Snailfish::ApplyExplosionRight(uint64_t* value) {
            if (isPair) {
                return pair[0].ApplyExplosionRight(value) || pair[1].ApplyExplosionRight(value);
            }
            this->value += *value;
            *value = 0;
            return true;
        }

        bool Snailfish::CheckSplits() {
            if (isPair) {
                return pair[0].CheckSplits() || pair[1].CheckSplits();
            }
            if (value >= 10) {
                uint64_t v1 = value / 2;
                uint64_t v2 = value - v1;
                isPair = true;
                pair.clear();
                pair.push_back(Snailfish(v1));
                pair.push_back(Snailfish(v2));
                return true;
            }
            return false;
        }

        Snailfish::Snailfish(int64_t value) {
            this->isPair = false;
            this->value = value;
        }

        Snailfish::Snailfish(const std::string& input, size_t& i) {
            LoadSnailfish(input, i);
        }

        Snailfish::Snailfish(Snailfish s1, Snailfish s2) {
            this->isPair = true;
            pair.clear();
            this->pair.push_back(s1);
            this->pair.push_back(s2);
        }

        Snailfish::Snailfish(const std::string& input) {
            size_t i = 0;
            LoadSnailfish(input, i);
        }

        uint64_t Snailfish::CalculateMagnitude() {
            if (isPair) {
                return 3 * pair[0].CalculateMagnitude() + 2 * pair[1].CalculateMagnitude();
            }
            return value;
        }

        void Snailfish::Reduce() {
            while (CheckExplosions() || CheckSplits()) {}
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            std::vector<Snailfish> allFish = {};
            for (auto& line : input) {
                allFish.push_back(Snailfish(line));
            };
            Snailfish fish = allFish[0];
            for (int i = 1; i < allFish.size(); i++) {
                fish = Snailfish(fish, allFish[i]);
                fish.Reduce();
            }
            auto endTime = std::chrono::high_resolution_clock::now();
            return { fish.CalculateMagnitude(), endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();
            std::vector<Snailfish> allFish = {};
            for (auto& line : input) {
                allFish.push_back(Snailfish(line));
            };

            uint64_t max = 0;
            for (int i = 0; i < allFish.size(); i++) {
                for (int j = 0; j < allFish.size(); j++) {
                    if (i != j) {
                        Snailfish fish(allFish[i], allFish[j]);
                        fish.Reduce();
                        max = std::max(max,fish.CalculateMagnitude());
                    }
                }
            }

            auto endTime = std::chrono::high_resolution_clock::now();
            return { max, endTime - startTime };
        }
    }
}