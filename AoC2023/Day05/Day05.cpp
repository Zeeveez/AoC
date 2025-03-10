#include <sstream>
#include <algorithm>

#include "Day05.h"

#include "../../Helpers/Helpers.h"

namespace AoC2023 {
    void Day05::Load() {
        input = AoC::Helpers::ReadLines("./Day05.txt");
    }

    void Day05::Parse() {
        std::istringstream iss(input[0]);
        std::string temp;
        iss >> temp; // Discard "seeds:"

        size_t token;
        while (iss >> token) {
            seeds.push_back(token);
        }

        almanac = Almanac(input);
        almanac.Flatten("seed");
    }

    void Day05::A() {
        size_t res = std::numeric_limits<size_t>::max();
        for (auto& seed : seeds) {
            res = std::min(res, almanac.Traverse("seed", "location", seed));
        }
        partAResult.first = res;
    }

    void Day05::B() {
        size_t res = std::numeric_limits<size_t>::max();
        for (size_t i = 0; i < seeds.size(); i += 2) {
            size_t minSeed = seeds[i];
            size_t range = seeds[i + 1];
            for (auto& map : almanac.sourceMaps["seed"].maps) {
                if (map.sourceStart < minSeed + range && minSeed < map.sourceStart + map.size) {
                    size_t seed = std::max(std::min(map.sourceStart, minSeed + range - 1), std::min(minSeed, map.sourceStart + map.size - 1));
                    res = std::min(res, almanac.Traverse("seed", "location", seed));
                }
            }
        }
        partBResult.first = res;
    }

    Day05::RangeMap::RangeMap(const std::string& input) {
        std::istringstream iss(input);
        iss >> destinationStart;
        iss >> sourceStart;
        iss >> size;
    }

    Day05::RangeMap::RangeMap(size_t destinationStart, size_t sourceStart, size_t size) {
        this->destinationStart = destinationStart;
        this->sourceStart = sourceStart;
        this->size = size;
    }

    bool Day05::RangeMap::Contains(size_t v) {
        return v >= sourceStart
            && v < sourceStart + size;
    }

    size_t Day05::RangeMap::Map(size_t v) {
        return destinationStart + v - sourceStart;
    }

    std::tuple<std::vector<Day05::RangeMap>, std::vector<Day05::RangeMap>, std::vector<Day05::RangeMap>> Day05::RangeMap::ReMap(RangeMap a, RangeMap b) {
        if (a.destinationStart == b.sourceStart && a.size == b.size) {
            a.destinationStart = b.destinationStart;
            return { { }, { a }, { } };
        }
        // No overlap
        if (a.destinationStart + a.size <= b.sourceStart) {
            return { { }, { }, { } };
        }
        if (a.destinationStart >= b.sourceStart + b.size) {
            return { { }, { }, { } };
        }

        std::vector<RangeMap> unmappable = {};
        std::vector<RangeMap> leftOvers = {};

        // Cut off excess A at start
        if (a.destinationStart < b.sourceStart) {
            auto missedSize = b.sourceStart - a.destinationStart;
            unmappable.push_back(RangeMap(a.destinationStart, a.sourceStart, missedSize));
            a.sourceStart += missedSize;
            a.destinationStart += missedSize;
            a.size -= missedSize;
            unmappable.push_back(a);
            leftOvers.push_back(b);
        }

        // Cut off excess B at start
        else if (b.sourceStart < a.destinationStart) {
            auto missedSize = a.destinationStart - b.sourceStart;
            leftOvers.push_back(RangeMap(b.destinationStart, b.sourceStart, missedSize));
            b.sourceStart += missedSize;
            b.destinationStart += missedSize;
            b.size -= missedSize;
            unmappable.push_back(a);
            leftOvers.push_back(b);
        }

        // Cut off excess A at end
        else if (b.sourceStart + b.size > a.destinationStart) {
            auto missedSize = a.destinationStart + a.size - b.sourceStart - b.size;
            unmappable.push_back(RangeMap(a.destinationStart + a.size - missedSize, a.sourceStart + a.size - missedSize, missedSize));
            a.size -= missedSize;
            unmappable.push_back(a);
            leftOvers.push_back(b);
        }

        // Cut off excess B at start
        else if (a.destinationStart + b.size > b.sourceStart) {
            auto missedSize = a.destinationStart - b.sourceStart;
            leftOvers.push_back(RangeMap(b.destinationStart + b.size - +missedSize, b.sourceStart + b.size - missedSize, missedSize));
            b.size -= missedSize;
            unmappable.push_back(a);
            leftOvers.push_back(b);
        }

        return { unmappable, { }, leftOvers };
    }

    Day05::SourceMap::SourceMap(const std::vector<std::string>& input, size_t& i) {
        source = input[i].substr(0, input[i].find('-'));
        destination = input[i].substr(input[i].find('-') + 4, input[i].find(' ') - source.length() - 4);

        while (++i < input.size() && input[i] != "") {
            maps.push_back(RangeMap(input[i]));
        }
    }

    size_t Day05::SourceMap::Map(size_t v) {
        for (auto& map : maps) {
            if (map.Contains(v)) {
                return map.Map(v);
            }
        }
        return v;
    }

    void Day05::SourceMap::MergeIn(const SourceMap& other) {
        std::vector<RangeMap> newMaps = {};
        std::vector<RangeMap> mapsToProcess = maps;
        std::vector<RangeMap> otherMapsToProcess = other.maps;

        while (mapsToProcess.size() && otherMapsToProcess.size()) {
            auto map = mapsToProcess[mapsToProcess.size() - 1]; mapsToProcess.pop_back();

            std::vector<RangeMap> newOtherMapsToProcess = {};
            for (size_t i = 0; i < otherMapsToProcess.size(); i++) {
                auto otherMap = otherMapsToProcess[i];

                auto [unmappable, remapped, leftOvers] = RangeMap::ReMap(map, otherMap);
                if (unmappable.size() || remapped.size() || leftOvers.size()) {
                    mapsToProcess.insert(mapsToProcess.begin(), unmappable.begin(), unmappable.end());
                    newMaps.insert(newMaps.begin(), remapped.begin(), remapped.end());
                    otherMapsToProcess.erase(otherMapsToProcess.begin() + i);
                    otherMapsToProcess.insert(otherMapsToProcess.begin(), leftOvers.begin(), leftOvers.end());
                    goto mapProcessed;
                }
            }

            // No overlap
            newMaps.push_back(map);

        mapProcessed:;
        }

        newMaps.insert(newMaps.begin(), mapsToProcess.begin(), mapsToProcess.end());
        newMaps.insert(newMaps.begin(), otherMapsToProcess.begin(), otherMapsToProcess.end());
        this->maps = newMaps;
        this->destination = other.destination;
    }

    Day05::Almanac::Almanac(const std::vector<std::string>& input) {
        size_t i = 1;
        while (++i < input.size()) {
            SourceMap map = SourceMap(input, i);
            sourceMaps[map.source] = map;
        }
    }

    size_t Day05::Almanac::Traverse(std::string source, std::string destination, size_t value) {
        do {
            if (sourceMaps[source].destination == destination) {
                return sourceMaps[source].Map(value);
            }
            value = sourceMaps[source].Map(value);
            source = sourceMaps[source].destination;
        } while (true);
    }

    void Day05::Almanac::Flatten(const std::string& start) {
        SourceMap& combinedMap = sourceMaps[start];
        while (sourceMaps.size() != 1) {
            auto oldDestination = combinedMap.destination;
            combinedMap.MergeIn(sourceMaps[oldDestination]);
            sourceMaps.erase(oldDestination);
        }
    }
}