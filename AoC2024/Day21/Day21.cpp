#include <map>

#include "Day21.h"
#include "../../Helpers/Helpers.h"


namespace AoC2024 {
    std::map<std::pair<char, char>, std::vector<std::string>> numericKeypad = {
        { { '7', '7' }, { "" } },
        { { '7', '8' }, { ">" } },
        { { '7', '9' }, { ">>" } },
        { { '7', '4' }, { "v" } },
        { { '7', '5' }, { "v>", ">v" } },
        { { '7', '6' }, { "v>>", ">>v" } },
        { { '7', '1' }, { "vv" } },
        { { '7', '2' }, { "vv>", ">vv" } },
        { { '7', '3' }, { "vv>>", ">>vv"} },
        { { '7', '0' }, { ">vvv" } },
        { { '7', 'A' }, { ">>vvv" } },
        { { '8', '7' }, { "<" } },
        { { '8', '8' }, { "" } },
        { { '8', '9' }, { ">" } },
        { { '8', '4' }, { "v<", "<v" } },
        { { '8', '5' }, { "v" } },
        { { '8', '6' }, { "v>", ">v" } },
        { { '8', '1' }, { "vv<", "<vv" } },
        { { '8', '2' }, { "vv" } },
        { { '8', '3' }, { "vv>", ">vv" } },
        { { '8', '0' }, { "vvv" } },
        { { '8', 'A' }, { "vvv>", ">vvv" } },
        { { '9', '7' }, { "<<" } },
        { { '9', '8' }, { "<" } },
        { { '9', '9' }, { "<" } },
        { { '9', '4' }, { "v<<", "<<v" } },
        { { '9', '5' }, { "v<", "<v" } },
        { { '9', '6' }, { "v" } },
        { { '9', '1' }, { "vv<<", "<<vv" } },
        { { '9', '2' }, { "vv<", "<vv" } },
        { { '9', '3' }, { "vv" } },
        { { '9', '0' }, { "vvv<", "<vvv" } },
        { { '9', 'A' }, { "vvv" } },
        { { '4', '7' }, { "^" } },
        { { '4', '8' }, { "^>", ">^" } },
        { { '4', '9' }, { "^>>", ">>^" } },
        { { '4', '4' }, { "" } },
        { { '4', '5' }, { ">" } },
        { { '4', '6' }, { ">>" } },
        { { '4', '1' }, { "v" } },
        { { '4', '2' }, { "v>", ">v" } },
        { { '4', '3' }, { ">>v", "v>>" } },
        { { '4', '0' }, { ">vv"}},
        { { '4', 'A' }, { ">>vv" } },
        { { '5', '7' }, { "^<", "<^" } },
        { { '5', '8' }, { "^" } },
        { { '5', '9' }, { "^>", ">^" } },
        { { '5', '4' }, { "<" } },
        { { '5', '5' }, { "" } },
        { { '5', '6' }, { ">" } },
        { { '5', '1' }, { "v<", "<v" } },
        { { '5', '2' }, { "v" } },
        { { '5', '3' }, { "v>", ">v" } },
        { { '5', '0' }, { "vv" } },
        { { '5', 'A' }, { "vv>", ">vv" } },
        { { '6', '7' }, { "^<<", "<<^" } },
        { { '6', '8' }, { "^<", "<^" } },
        { { '6', '9' }, { "^" } },
        { { '6', '4' }, { "<<" } },
        { { '6', '5' }, { "<" } },
        { { '6', '6' }, { "" } },
        { { '6', '1' }, { "v<<", "<<v" } },
        { { '6', '2' }, { "v<", "<v" } },
        { { '6', '3' }, { "v" } },
        { { '6', '0' }, { "vv<", "<vv" } },
        { { '6', 'A' }, { "vv" } },
        { { '1', '7' }, { "^^" } },
        { { '1', '8' }, { "^^>", ">^^" } },
        { { '1', '9' }, { "^^>>", ">>^^" } },
        { { '1', '4' }, { "^" } },
        { { '1', '5' }, { "^>", ">^" } },
        { { '1', '6' }, { "^>>", ">>^" } },
        { { '1', '1' }, { "" } },
        { { '1', '2' }, { ">" } },
        { { '1', '3' }, { ">>" } },
        { { '1', '0' }, { ">v" } },
        { { '1', 'A' }, { ">>v" } },
        { { '2', '7' }, { "^^<", "<^^" } },
        { { '2', '8' }, { "^^" } },
        { { '2', '9' }, { "^^>", ">^^" } },
        { { '2', '4' }, { "^<","<^" } },
        { { '2', '5' }, { "^" } },
        { { '2', '6' }, { "^>", ">^" } },
        { { '2', '1' }, { "<" } },
        { { '2', '2' }, { "" } },
        { { '2', '3' }, { ">" } },
        { { '2', '0' }, { "v" } },
        { { '2', 'A' }, { "v>", ">v" } },
        { { '3', '7' }, { "^^<<", "<<^^" } },
        { { '3', '8' }, { "^^<", "<^^" } },
        { { '3', '9' }, { "^^" } },
        { { '3', '4' }, { "^<<", "<<^" } },
        { { '3', '5' }, { "^<", "^<" } },
        { { '3', '6' }, { "^" } },
        { { '3', '1' }, { "<<" } },
        { { '3', '2' }, { "<" } },
        { { '3', '3' }, { "" } },
        { { '3', '0' }, { "v<", "<v" } },
        { { '3', 'A' }, { "v" } },
        { { '0', '7' }, { "^^^<" } },
        { { '0', '8' }, { "^^^" } },
        { { '0', '9' }, { "^^^>", ">^^^" } },
        { { '0', '4' }, { "^^<" } },
        { { '0', '5' }, { "^^" } },
        { { '0', '6' }, { "^^>", ">^^" } },
        { { '0', '1' }, { "^<" } },
        { { '0', '2' }, { "^" } },
        { { '0', '3' }, { "^>", ">^" } },
        { { '0', '0' }, { "" } },
        { { '0', 'A' }, { ">" } },
        { { 'A', '7' }, { "^^^<<" } },
        { { 'A', '8' }, { "^^^<", "<^^^" } },
        { { 'A', '9' }, { "^^^" } },
        { { 'A', '4' }, { "^^<<" } },
        { { 'A', '5' }, { "^^<", "<^^" } },
        { { 'A', '6' }, { "^^" } },
        { { 'A', '1' }, { "^<<" } },
        { { 'A', '2' }, { "^<", "<^" } },
        { { 'A', '3' }, { "^" } },
        { { 'A', '0' }, { "<" } },
        { { 'A', 'A' }, { "" } },
    };

    std::map<std::pair<char, char>, std::vector<std::string>> directionalKeypad = {
        { { '^', '^' }, { "" } },
        { { '^', 'A' }, { ">" } },
        { { '^', '<' }, { "v<" } },
        { { '^', 'v' }, { "v" } },
        { { '^', '>' }, { "v>", ">v" } },
        { { 'A', '^' }, { "<" } },
        { { 'A', 'A' }, { "" } },
        { { 'A', '<' }, { "v<<" } },
        { { 'A', 'v' }, { "v<", "<v" } },
        { { 'A', '>' }, { "v" } },
        { { '<', '^' }, { ">^" } },
        { { '<', 'A' }, { ">>^" } },
        { { '<', '<' }, { "" } },
        { { '<', 'v' }, { ">" } },
        { { '<', '>' }, { ">>" } },
        { { 'v', '^' }, { "^" } },
        { { 'v', 'A' }, { "^>", ">^" } },
        { { 'v', '<' }, { "<" } },
        { { 'v', 'v' }, { "" } },
        { { 'v', '>' }, { ">" } },
        { { '>', '^' }, { "^<", "<^" } },
        { { '>', 'A' }, { "^" } },
        { { '>', '<' }, { "<<" } },
        { { '>', 'v' }, { "<" } },
        { { '>', '>' }, { "" } },
    };

    void Day21::Load() {
        input = AoC::Helpers::ReadLines("./Day21.txt");
    }

    void Day21::Parse() {
        // No parsing required
    }

    std::map<std::tuple<char, std::string, int, int>, uint64_t> memory;

    uint64_t Day21::ShortestSequence(char pos, std::string sequence, int depth, int maxDepth) {
        if (depth == maxDepth) { return 0; }
        if (sequence.length() == 0) { return 0; }

        auto it = memory.find({ pos, sequence, depth, maxDepth });
        if (it != memory.end()) { return it->second; }
        uint64_t minLength = std::numeric_limits<uint64_t>::max();

        for (auto& subsequence : (depth == 0 ? numericKeypad : directionalKeypad).at({ pos, sequence[0] })) {
            minLength = std::min(minLength, subsequence.length() + ShortestSequence('A', subsequence + 'A', depth + 1, maxDepth) + ShortestSequence(sequence[0], sequence.substr(1), depth, maxDepth));
        }

        memory[{pos, sequence, depth, maxDepth}] = minLength;

        return minLength;
    }

    void Day21::A() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = 0;

        for (auto& sequence : input) {
            auto shortestSequence = ShortestSequence('A', sequence, 0, 3) + sequence.length();  // Why add sequence length??????
            res += shortestSequence * std::stoi(sequence);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        partAResult = { res, endTime - startTime };
    }

    void Day21::B() {
        auto startTime = std::chrono::high_resolution_clock::now();

        uint64_t res = 0;

        for (auto& sequence : input) {
            auto shortestSequence = ShortestSequence('A', sequence, 0, 26) + sequence.length();  // Why add sequence length??????
            res += shortestSequence * std::stoi(sequence);
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        partBResult = { res, endTime - startTime };
    }
}