#ifndef DAY13_H
#define DAY13_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day13 {
        class Item {
        private:
            bool isValue;
            int value;
            std::vector<Item> items;

            void LoadData(std::string line, int& i);
            Item(int i);
            Item(std::vector<int> values);
            Item(std::string line, int& i);
        public:
            Item(std::string line);

            void Print();

            friend bool operator<(const Item& l, const Item& r);
            friend bool operator==(const Item& l, const Item& r);
            friend bool operator!=(const Item& l, const Item& r);
        };
        
        std::vector<Item> PreProcessInput(const std::vector<std::string>& input);

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif