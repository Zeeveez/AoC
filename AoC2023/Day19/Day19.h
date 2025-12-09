#ifndef DAY19_H
#define DAY19_H

#include <cstdint>
#include <vector>
#include <chrono>
#include <string>
#include <functional>
#include <map>

namespace AoC2023::Day19 {
    enum RatingType {
        ExtremelyCoolLooking,
        Musical,
        Aerodynamic,
        Shiny
    };

    class Part {
    public:
        std::unordered_map<RatingType, int> ratings = {};

        Part() = default;
        Part(const std::string& part);
    };

    class WorkflowRule {
    public:
        std::optional<RatingType> check;
        char conditionLabel = '<';
        std::function<bool(int, int)> condition = std::less<int>();
        int threshold;
        std::string destination;

        WorkflowRule() = default;
        WorkflowRule(const std::string& workflow, int& pos);
    };

    class Workflow {
    public:
        std::string label;
        std::vector<WorkflowRule> rules = {};

        Workflow() = default;
        Workflow(const std::string& workflow);
        std::string ProcessPart(const Part& part) const;
    };

    std::string ProcessPart(const Part& part, const std::map<std::string, Workflow>& workflows);

    std::pair<std::map<std::string, Workflow>, std::vector<Part>> ParseInput(const std::vector<std::string>& input);

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input);
    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input);
}
#endif