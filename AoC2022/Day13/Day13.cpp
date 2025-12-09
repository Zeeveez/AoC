#include "Day13.h"

#include <iostream>
#include <algorithm>

namespace AoC2022 {
    namespace Day13 {
        void Item::LoadData(std::string line, int& i) {
            if (line[i] == '[') {
                isValue = false;
                items = {};
                i++;
                while (line[i] != ']') {
                    items.push_back(Item(line, i));
                    if (line[i] == ',') { i++; }
                }
                i++;
            }
            else {
                isValue = true;
                value = 0;
                while (line[i] != ',' && line[i] != ']') {
                    value = value * 10 + line[i] - '0';
                    i++;
                }
            }
        }

        Item::Item(int i) {
            isValue = true;
            value = i;
            items = { };
        }

        Item::Item(std::vector<int> values) {
            isValue = false;
            this->value = 0;
            for (auto& value : values) {
                items.push_back(Item(value));
            }
        }

        Item::Item(std::string line, int& i) {
            LoadData(line, i);
        }

        Item::Item(std::string line) {
            int i = 0;
            LoadData(line, i);
        }

        bool operator<(const Item& l, const Item& r) {
            if (l.isValue && r.isValue) { return l.value < r.value; }
            if (l.isValue && !r.isValue) {
                std::vector<int> data = { l.value };
                return Item(data) < r;
            }
            if (!l.isValue && r.isValue) {
                std::vector<int> data = { r.value };
                return l < Item(data);
            }

            for (int i = 0; i < l.items.size() && i < r.items.size(); i++) {
                if (l.items[i] < r.items[i]) { return true; }
                if (l.items[i] != r.items[i]) { return false; }
            }
            return l.items.size() < r.items.size();
        }
        bool operator==(const Item& l, const Item& r) {
            if (l.isValue && r.isValue) { return l.value == r.value; }
            if (l.isValue && !r.isValue) {
                std::vector<int> data = { l.value };
                return Item(data) == r;
            }
            if (!l.isValue && r.isValue) {
                std::vector<int> data = { r.value };
                return l == Item(data);
            }
            if (l.items.size() != r.items.size()) { return false; }

            for (int i = 0; i < l.items.size() && i < r.items.size(); i++) {
                if (l.items[i] != r.items[i]) { return false; }
            }
            return true;
        }
        bool operator!=(const Item& l, const Item& r) {
            return !(l == r);
        }

        void Item::Print() {
            if (isValue) {
                std::cout << value;
            }
            else {
                std::cout << '[';
                for (int i = 0; i < items.size(); i++) {
                    if (i != 0) { std::cout << ','; }
                    items[i].Print();
                }
                std::cout << ']';
            }
        }

        std::vector<Item> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<Item> items = {};
            for (int i = 0; i < input.size(); i++) {
                if (input[i] == "") { continue; }
                items.push_back(Item(input[i]));
            }
            return items;
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto items = PreProcessInput(input);
            int res = 0;
            for (int i = 0; i < items.size() / 2; i++) {
                if (items[i * 2] < items[i * 2 + 1]) {
                    res += i + 1;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            auto items = PreProcessInput(input);
            auto dividers = PreProcessInput({ "[[2]]", "[[6]]" });
            items.insert(items.end(), dividers.begin(), dividers.end());
            std::sort(items.begin(), items.end());

            int res = 1;
            for (int i = 0; i < items.size(); i++) {
                if (items[i] == dividers[0] || items[i] == dividers[1]) {
                    res *= i + 1;
                }
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { res, endtime - starttime };
        }
    }
}