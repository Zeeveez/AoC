#include "Day07.h"

namespace AoC2022 {
    namespace Day07 {
        File::File(uint64_t size, std::string name) {
            this->size = size;
            this->name = name;
        }

        Dir::Dir(std::string name) {
            this->name = name;
        }

        Dir Dir::LoadStructure(std::vector<std::string> structure) {
            std::vector<std::string> workingDir = { };
            Dir root = Dir("/");
            for (auto& line : structure) {
                if (line[0] == '$') {
                    if (line[2] == 'l') { /* Do nothing, files follow */ }
                    else if (line[5] == '.') {
                        // cd ..
                        workingDir.pop_back();
                    }
                    else if (line[5] == '/') {
                        // cd /
                        workingDir = { };
                    }
                    else {
                        // cd <folder>
                        workingDir.push_back(line.substr(5));
                    }
                }
                else if (line[0] == 'd') {
                    // directory listing
                    root.Navigate(workingDir)->AddDir(Dir(line.substr(4)));
                }
                else {
                    // file listing
                    size_t sep = line.find(' ');
                    root.Navigate(workingDir)->AddFile(File(std::stoi(line.substr(0, sep)), line.substr(sep + 1)));
                }
            }
            return root;
        }

        void Dir::AddFile(File file) {
            this->files.push_back(file);
        }

        void Dir::AddDir(Dir dir) {
            this->dirs.push_back(dir);
        }

        uint64_t Dir::GetSize() {
            uint64_t size = 0;
            for (auto& file : files) {
                size += file.size;
            }
            for (auto& dir : dirs) {
                size += dir.GetSize();
            }
            return size;
        }

        Dir* Dir::Navigate(std::vector<std::string>& path) {
            Dir* currentDir = this;
            for (auto& pathSegment : path) {
                for (auto& dir : currentDir->dirs) {
                    if (dir.name == pathSegment) {
                        currentDir = &dir;
                        break;
                    }
                }
            }
            return currentDir;
        }

        uint64_t Dir::GetSumOfFoldersBelowSize(uint64_t threshold) {
            uint64_t totalSize = 0;
            if (this->GetSize() <= threshold) {
                totalSize += this->GetSize();
            }
            for (auto& dir : dirs) {
                totalSize += dir.GetSumOfFoldersBelowSize(threshold);
            }
            return totalSize;
        }

        void Dir::GetDirectoriesExceedingSize(uint64_t threshold, std::vector<Dir*>& dirs) {
            if (this->GetSize() >= threshold) {
                dirs.push_back(this);
            }
            for (auto& dir : this->dirs) {
                dir.GetDirectoriesExceedingSize(threshold, dirs);
            }
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto starttime = std::chrono::high_resolution_clock::now();

            Dir root = Dir::LoadStructure(input);
            auto size = root.GetSumOfFoldersBelowSize(100000);

            auto endtime = std::chrono::high_resolution_clock::now();
            return { size, endtime - starttime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            Dir root = Dir::LoadStructure(input);

            // Total size       = 70_000_000
            // Needed size      = 30_000_000
            // Available size   = 40_000_000
            // Current size     = root.GetSize()
            // Size to delete   = current - avail.
            std::vector<Dir*> possibleDeletions = {};
            root.GetDirectoriesExceedingSize(root.GetSize() - 40'000'000, possibleDeletions);

            uint64_t size = 70'000'000;
            for (auto& dir : possibleDeletions) {
                size = std::min(size, dir->GetSize());
            }

            auto endtime = std::chrono::high_resolution_clock::now();
            return { size, endtime - startTime };
        }
    }
}