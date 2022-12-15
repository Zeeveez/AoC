#ifndef DAY07_H
#define DAY07_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>

namespace AoC2022 {
    namespace Day07 {
        class File {
        public:
            std::string name;
            uint64_t size;

            File(uint64_t size, std::string name);
        };

        class Dir {
        public:
            std::string name;
            std::vector<File> files;
            std::vector<Dir> dirs;

            Dir(std::string name);
            static Dir LoadStructure(std::vector<std::string> structure);
            void AddFile(File file);
            void AddDir(Dir dir);
            uint64_t GetSize();
            Dir* Navigate(std::vector<std::string>& path);
            uint64_t GetSumOfFoldersBelowSize(uint64_t threshold);
            void GetDirectoriesExceedingSize(uint64_t threshold, std::vector<Dir*>& dirs);
        };

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
    }
}
#endif