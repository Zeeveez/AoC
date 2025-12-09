#include "Day08.h"
#include "../../Helpers/Helpers.h"

#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <algorithm>

namespace AoC2025 {
    void Day08::Parse() {
        sockets = {};
        for (auto& line : rawData) {
            int v1 = 0;
            int v2 = 0;
            int v3 = 0;
            int n = 0;
            for (auto& c : line) {
                if (c == ',') { n++; }
                else if (n == 0) { v1 = v1 * 10 + c - '0'; }
                else if (n == 1) { v2 = v2 * 10 + c - '0'; }
                else if (n == 2) { v3 = v3 * 10 + c - '0'; }
            }
            sockets.push_back(Vec3{ .x = v1, .y = v2, .z = v3 });
        }
    }

    AoC::DayResult::PuzzleResult Day08::A() {
        std::unordered_map<int, std::vector<Vec3*>> networks = {};
        auto socketDistances = GetSocketDistances();

        for (int i = 0; i < 1000; i++) {
            auto& [_, minIdx1, minIdx2] = socketDistances[i];
            AddToNetworks(networks, minIdx1, minIdx2);
        }

        std::vector<std::int64_t> networkSizes = {};
        for (auto& network : networks) {
            if (network.second.size() != 0) {
                networkSizes.push_back(network.second.size());
            }
        }
        std::sort(networkSizes.begin(), networkSizes.end(), std::greater<>());

        return networkSizes[0] * networkSizes[1] * networkSizes[2];
    }

    AoC::DayResult::PuzzleResult Day08::B() {
        std::unordered_map<int, std::vector<Vec3*>> networks = {};
        auto socketDistances = GetSocketDistances();

        for (int i = 0;; i++) {
            auto& [_, minIdx1, minIdx2] = socketDistances[i];
            AddToNetworks(networks, minIdx1, minIdx2);

            if (networks[sockets[minIdx1].network].size() == sockets.size()) {
                return sockets[minIdx1].x * sockets[minIdx2].x;
            }
        }

        return -1;
    }

    std::vector<std::tuple<std::uint64_t, std::size_t, std::size_t>> Day08::GetSocketDistances() {
        std::vector<std::tuple<std::uint64_t, std::size_t, std::size_t>> distances = {};
        for (std::size_t s1 = 0; s1 < sockets.size(); s1++) {
            for (std::size_t s2 = s1 + 1; s2 < sockets.size(); s2++) {
                distances.push_back({ sockets[s1].Dist(sockets[s2]), s1, s2 });
            }
        }
        std::sort(
            distances.begin(),
            distances.end(),
            [](std::tuple<std::uint64_t, std::size_t, std::size_t> const& a, std::tuple<std::uint64_t, std::size_t, std::size_t> const& b)
            {
                return std::get<0>(a) < std::get<0>(b);
            });
        return distances;
    }

    void Day08::AddToNetworks(std::unordered_map<int, std::vector<Vec3*>>& networks, std::size_t idx1, std::size_t idx2) {
        if (sockets[idx1].network == -1 && sockets[idx2].network == -1) {
            // Neither in network, new network needed
            int networkID = networks.size();
            sockets[idx1].network = networkID;
            sockets[idx2].network = networkID;
            networks[networkID] = { &sockets[idx1], &sockets[idx2] };
        }
        else if (sockets[idx1].network == -1) {
            // Socket 0 needs network, but Socket 1 in network
            int networkID = sockets[idx2].network;
            sockets[idx1].network = networkID;
            networks[networkID].push_back(&sockets[idx1]);
        }
        else if (sockets[idx2].network == -1) {
            // Socket 1 needs network, but Socket 0 in network
            int networkID = sockets[idx1].network;
            sockets[idx2].network = networkID;
            networks[networkID].push_back(&sockets[idx2]);
        }
        else if (sockets[idx1].network == sockets[idx2].network) {
            // In same network, do nothing
        }
        else {
            // Different networks, merge
            int newNetworkID = sockets[idx1].network;
            int oldNetworkID = sockets[idx2].network;
            for (auto& socket : networks[oldNetworkID]) {
                socket->network = newNetworkID;
                networks[newNetworkID].push_back(socket);
            }
            networks[oldNetworkID] = {};
        }
    }
}