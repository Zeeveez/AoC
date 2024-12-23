#ifndef HELPERS_H
#define HELPERS_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace AoC {
    namespace Helpers {
        std::string ParseDrawnString(const std::vector<std::vector<bool>>& drawnString);
        std::vector<std::string> ReadLines(std::string path);

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

        template<typename T>
        std::vector<std::vector<T>> ReadTokenGrid(std::string path) {
            auto lines = ReadLines(path);
            std::vector<std::vector<T>> v = {};

            T n;
            for (auto& line : lines) {
                auto s = std::stringstream(line);
                std::vector<T> lv;
                while (s >> n) {
                    lv.push_back(n);
                }
                v.push_back(lv);
            }

            return v;
        }


        template<typename T>
        T ReadToken(std::string path) {
            std::fstream f(path);
            T v;
            f >> v;
            return v;
        }


        std::vector<std::string> SplitString(std::string str, char sep);
        std::vector<int> ReadCommaDelimitedList(std::string path);
    }
}
#endif