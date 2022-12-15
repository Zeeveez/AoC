#ifndef HELPERS_H
#define HELPERS_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

namespace AoC {
    namespace Helpers {
        std::string ParseDrawnString(const std::vector<std::vector<bool>>& drawnString);

        template<typename T>
        std::vector<T> ReadTokens(std::string path) {
            std::fstream f(path);
            std::vector<T> v = {};

            T n;
            while (f >> n) {
                v.push_back(n);
            }

            return v;
        }

        std::vector<std::string> ReadLines(std::string path);

        template<typename T>
        T ReadToken(std::string path) {
            std::fstream f(path);
            T v;
            f >> v;
            return v;
        }

        std::vector<int> ReadCommaDelimitedList(std::string path);
    }
}
#endif