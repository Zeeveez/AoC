#include "Day23.h"

#include <cctype>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include <algorithm>

#include <iostream>

namespace AoC2021 {
    namespace Day23 {
        std::vector<std::vector<int>> PreProcessInput(const std::vector<std::string>& input) {
            std::vector<std::vector<int>> tempInput = { {} };
            // Parse:
            //```
            //#D#C#B#A#
            //#D#B#A#C#
            //```
            // Into:
            // {
            //    { 4, 3, 2, 1 }
            //    { 4, 2, 1, 3 }
            // }
            for (auto& line : input) {
                for (auto& c : line) {
                    if (std::isalpha(c)) {
                        if (tempInput[tempInput.size() - 1].size() >= 4) {
                            tempInput.push_back({});
                        }
                        tempInput[tempInput.size() - 1].push_back(c - 'A' + 1);
                    }
                }
            }

            // Change:
            // {
            //    { 4, 3, 2, 1 }
            //    { 4, 2, 1, 3 }
            // }
            // Into:
            // {
            //    { 4, 4 }
            //    { 3, 4 }
            //    { 2, 1 }
            //    { 1, 3 }
            // }
            std::vector<std::vector<int>> output = { };
            for (int i = 0; i < tempInput[0].size(); i++) {
                output.push_back({});
                for (int j = 0; j < tempInput.size(); j++) {
                    output[i].push_back(tempInput[j][i]);
                }
            }
            return output;
        }

        void AddPartB(std::vector<std::string>& input) {
            // Add:
            //```
            //#D#C#B#A#
            //#D#B#A#C#
            //```
            // after 3rd row.
            // Adding in reverse so can use same index for both insertions
            input.insert(input.begin() + 3, "#D#B#A#C#");
            input.insert(input.begin() + 3, "#D#C#B#A#");
        }

        std::vector<std::tuple<std::pair<int, int>, int, uint64_t>> GetMoves(const std::vector<std::vector<int>>& currentRooms, const std::vector<int>& hallway) {
            const std::unordered_set<int> hallwayWaitAreas = { 0, 1, 3, 5, 7, 9, 10 };
            const std::unordered_map<int, int> roomEntrances = { { 0, 2 }, { 1, 4 }, { 2, 6 }, { 3, 8 } };
            const std::unordered_map<int, int> moveCosts = { { 1, 1 }, { 2, 10 }, { 3, 100 }, { 4, 1000 } };
            std::vector<std::tuple<std::pair<int, int>, int, uint64_t>> moves = {};

            // Check hallway moves
            for (int hallwaySquare = 0; hallwaySquare < hallway.size(); hallwaySquare++) {
                if (hallway[hallwaySquare] != 0) {
                    int mover = hallway[hallwaySquare];
                    int targetRoom = mover - 1;

                    // Check if target room has incorrect amphipods
                    bool canEnterRoom = true;
                    for (auto& inRoom : currentRooms[targetRoom]) {
                        if (inRoom != 0 && inRoom != mover) {
                            canEnterRoom = false; break;
                        }
                    }
                    if (!canEnterRoom) { continue; }

                    int targetHallway = roomEntrances.at(targetRoom);

                    // Check if target room is reachable
                    bool canReachRoom = true;
                    for (int j = std::min(hallwaySquare, targetHallway); j <= std::max(hallwaySquare, targetHallway); j++) {
                        if (j != hallwaySquare && hallway[j] != 0) {
                            canReachRoom = false; break;
                        }
                    }
                    if (!canReachRoom) { continue; }

                    // Can enter and can reach room, calculate movement
                    int hallwayMovement = std::max(hallwaySquare, targetHallway) - std::min(hallwaySquare, targetHallway);
                    int roomMovement = 0;
                    for (int j = 0; j < currentRooms[targetRoom].size(); j++) {
                        if (currentRooms[targetRoom][j] == 0) {
                            roomMovement++;
                        }
                        else {
                            break;
                        }
                    }

                    uint64_t moveCost = (hallwayMovement + roomMovement) * moveCosts.at(hallway[hallwaySquare]);

                    // Add move to list
                    moves.push_back({ { targetRoom, roomMovement - 1 }, hallwaySquare, moveCost });
                }
            }

            for (int room = 0; room < currentRooms.size(); room++) {
                int roomDepth = -1;
                for (int j = 0; j < currentRooms[room].size(); j++) {
                    if (currentRooms[room][j] != 0) {
                        if (currentRooms[room][j] != room + 1) {  // Someone in incorrect room
                            roomDepth = j; goto goLoopBreak;
                        }
                        else {  // Someone in correct room, check if others in the room are correct too
                            for (int k = j; k < currentRooms[room].size(); k++) {
                                if (currentRooms[room][k] != room + 1) {  // Someone else in incorrect room, need to move out of the way
                                    roomDepth = j; goto goLoopBreak;
                                }
                            }
                        }
                    }
                }
                if (roomDepth == -1) { continue; }
            goLoopBreak:
                int mover = currentRooms[room][roomDepth];
                int hallwayEntrance = roomEntrances.at(room);

                for (auto& destination : hallwayWaitAreas) {
                    bool canReachSquare = true;
                    // Check if target hallway square is reachable
                    for (int j = std::min(hallwayEntrance, destination); j <= std::max(hallwayEntrance, destination); j++) {
                        if (hallway[j] != 0) {
                            canReachSquare = false; break;
                        }
                    }
                    if (!canReachSquare) { continue; }
                    int hallwayMovement = std::max(hallwayEntrance, destination) - std::min(hallwayEntrance, destination);

                    uint64_t moveCost = (hallwayMovement + roomDepth + 1) * moveCosts.at(mover);

                    // Add move to list
                    moves.push_back({ { room, roomDepth }, destination, moveCost });
                }
            }

            // Check movement from room into hallway
            return moves;
        }

        uint64_t Solve(std::vector<std::vector<int>>& currentRooms, std::vector<int>& hallway, int depth) {
            if (depth > 50) { return std::numeric_limits<uint64_t>::max(); }
            auto moves = GetMoves(currentRooms, hallway);
            if (moves.size() == 0) {
                if (std::all_of(currentRooms[0].begin(), currentRooms[0].end(), [](int i) { return i == 1; })
                    && std::all_of(currentRooms[1].begin(), currentRooms[1].end(), [](int i) { return i == 2; })
                    && std::all_of(currentRooms[2].begin(), currentRooms[2].end(), [](int i) { return i == 3; })
                    && std::all_of(currentRooms[3].begin(), currentRooms[3].end(), [](int i) { return i == 4; })) {
                    return 0;
                }
                else {
                    return std::numeric_limits<uint64_t>::max();
                }
            }

            auto min = std::numeric_limits<uint64_t>::max();
            for (auto& move : moves) {
                int room = std::get<0>(move).first;
                int roomPos = std::get<0>(move).second;
                int hallwayPos = std::get<1>(move);

                int temp = hallway[hallwayPos];
                hallway[hallwayPos] = currentRooms[room][roomPos];
                currentRooms[room][roomPos] = temp;

                auto score = Solve(currentRooms, hallway, depth + 1);
                if (score != std::numeric_limits<uint64_t>::max()) {
                    min = std::min(std::get<2>(move) + score, min);
                }

                currentRooms[room][roomPos] = hallway[hallwayPos];
                hallway[hallwayPos] = temp;
            }
            return min;
        }

        uint64_t Solve(std::vector<std::vector<int>>& currentRooms) {
            std::vector<int> hallway = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            return Solve(currentRooms, hallway);
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            auto positions = PreProcessInput(input);
            auto cost = Solve(positions);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { cost, endTime - startTime };
        }

        std::pair<uint64_t, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
            auto startTime = std::chrono::high_resolution_clock::now();

            std::vector<std::string> modifiedInput = input;
            AddPartB(modifiedInput);
            auto positions = PreProcessInput(modifiedInput);
            auto cost = Solve(positions);

            auto endTime = std::chrono::high_resolution_clock::now();
            return { cost, endTime - startTime };
        }
    }
}