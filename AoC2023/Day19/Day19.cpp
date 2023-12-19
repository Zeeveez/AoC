#include "Day19.h"

#include <iostream>
#include <regex>

namespace AoC2023::Day19 {
    Part::Part(const std::string& part) {
        std::string::const_iterator ratingSearch(part.cbegin());
        static const std::regex ratingRe("([xmas])=(\\d+)", std::regex::optimize);
        std::smatch ratingMatch;
        while (std::regex_search(ratingSearch, part.cend(), ratingMatch, ratingRe)) {
            switch (ratingMatch[1].str()[0]) {
            case 'x':
                ratings[RatingType::ExtremelyCoolLooking] = std::stoi(ratingMatch[2]);
                break;
            case 'm':
                ratings[RatingType::Musical] = std::stoi(ratingMatch[2]);
                break;
            case 'a':
                ratings[RatingType::Aerodynamic] = std::stoi(ratingMatch[2]);
                break;
            case 's':
                ratings[RatingType::Shiny] = std::stoi(ratingMatch[2]);
                break;
            }
            ratingSearch = ratingMatch.suffix().first;
        }
    }

    WorkflowRule::WorkflowRule(const std::string& workflow, int& pos) {
        bool hasRule = workflow[pos + 1] == '<' || workflow[pos + 1] == '>';
        if (hasRule) {
            switch (workflow[pos]) {
            case 'x':
                check = RatingType::ExtremelyCoolLooking;
                break;
            case 'm':
                check = RatingType::Musical;
                break;
            case 'a':
                check = RatingType::Aerodynamic;
                break;
            case 's':
                check = RatingType::Shiny;
                break;
            }

            conditionLabel = workflow[pos + 1];
            switch (workflow[pos + 1]) {
            case '>':
                condition = std::greater<int>();
                break;
            case '<':
                condition = std::less<int>();
                break;
            }

            threshold = std::stoi(workflow.substr(pos + 2, workflow.find(':', pos) - pos - 2));

            int endPos = workflow.find(',', pos);
            destination = workflow.substr(workflow.find(':', pos) + 1, endPos - workflow.find(':', pos) - 1);

            pos = endPos + 1;
        }
        else {
            int endPos = workflow.find(',', pos);
            if (endPos == std::string::npos) {
                endPos = workflow.find('}');
            }
            destination = workflow.substr(pos, endPos - pos);
            pos = endPos + 1;
        }
    }

    Workflow::Workflow(const std::string& workflow) {
        label = workflow.substr(0, workflow.find('{'));
        int pos = workflow.find('{') + 1;
        while (pos < workflow.length()) {
            rules.push_back(WorkflowRule(workflow, pos));
        }
    }

    std::string Workflow::ProcessPart(const Part& part) const {
        for (auto& rule : rules) {
            if (rule.check.has_value()) {
                if (rule.condition(part.ratings.at(rule.check.value()), rule.threshold)) {
                    return rule.destination;
                }
            }
            else {
                return rule.destination;
            }
        }
    }

    std::pair<std::map<std::string, Workflow>, std::vector<Part>> ParseInput(const std::vector<std::string>& input) {
        std::map<std::string, Workflow> workflows = {};
        std::vector<Part> parts = {};

        for (const auto& line : input) {
            if (line.length() == 0) { continue; }

            if (line[0] == '{') {
                parts.push_back(Part(line));
            }
            else {
                // Workflow
                auto workflow = Workflow(line);
                workflows[workflow.label] = workflow;
            }
        }

        return { workflows, parts };
    }

    std::string ProcessPart(const Part& part, const std::map<std::string, Workflow>& workflows) {
        std::string nextWorkflow = "in";
        while (nextWorkflow != "A" && nextWorkflow != "R") {
            nextWorkflow = workflows.at(nextWorkflow).ProcessPart(part);
        }
        return nextWorkflow;
    }

    void GetPossibleCombinations(const std::map<std::string, Workflow>& workflows, uint64_t& totalPossible, std::map<RatingType, std::pair<int, int>> bounds, std::string currentWorkflow) {
        if (currentWorkflow == "R") {
            // None of bounds are valid
            return;
        }
        else if (currentWorkflow == "A") {
            // All of bounds are valid
            uint64_t possible = 1;
            for (auto& [rating, ratingBounds] : bounds) {
                if (ratingBounds.first > ratingBounds.second) { return; }
                possible *= ratingBounds.second - ratingBounds.first + 1;
            }
            totalPossible += possible;
            return;
        }

        for (auto& rule : workflows.at(currentWorkflow).rules) {
            if (rule.check.has_value()) {
                if (rule.conditionLabel == '<') {
                    auto oldBounds = bounds[rule.check.value()].second;
                    bounds[rule.check.value()].second = std::min(bounds[rule.check.value()].second, rule.threshold - 1);
                    GetPossibleCombinations(workflows, totalPossible, bounds, rule.destination);
                    bounds[rule.check.value()].second = oldBounds;
                    bounds[rule.check.value()].first = std::max(bounds[rule.check.value()].first, rule.threshold);
                }
                else {
                    auto oldBounds = bounds[rule.check.value()].first;
                    bounds[rule.check.value()].first = std::max(bounds[rule.check.value()].first, rule.threshold + 1);
                    GetPossibleCombinations(workflows, totalPossible, bounds, rule.destination);
                    bounds[rule.check.value()].first = oldBounds;
                    bounds[rule.check.value()].second = std::min(bounds[rule.check.value()].second, rule.threshold);
                }
            }
            else {
                GetPossibleCombinations(workflows, totalPossible, bounds, rule.destination);
            }
        }
    }

    uint64_t GetPossibleCombinations(const std::map<std::string, Workflow>& workflows) {
        uint64_t totalPossible = 0;
        GetPossibleCombinations(
            workflows,
            totalPossible,
            {
                { RatingType::ExtremelyCoolLooking, { 1, 4000 } },
                { RatingType::Musical, { 1, 4000 } },
                { RatingType::Aerodynamic, { 1, 4000 } },
                { RatingType::Shiny, { 1, 4000 } },
            },
            "in"
            );
        return totalPossible;
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> A(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto [workflows, parts] = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        int64_t score = 0;

        for (const auto& part : parts) {
            if (ProcessPart(part, workflows) == "A") {
                score += part.ratings.at(RatingType::ExtremelyCoolLooking);
                score += part.ratings.at(RatingType::Musical);
                score += part.ratings.at(RatingType::Aerodynamic);
                score += part.ratings.at(RatingType::Shiny);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }

    std::tuple<uint64_t, std::chrono::duration<double, std::milli>, std::chrono::duration<double, std::milli>> B(const std::vector<std::string>& input) {
        auto parseStart = std::chrono::high_resolution_clock::now();
        auto [workflows, parts] = ParseInput(input);
        auto parseEnd = std::chrono::high_resolution_clock::now();

        auto startTime = std::chrono::high_resolution_clock::now();

        int64_t score = GetPossibleCombinations(workflows);

        auto endTime = std::chrono::high_resolution_clock::now();
        return { score, parseEnd - parseStart, endTime - startTime };
    }
}