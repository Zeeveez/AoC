#pragma once

#include <vector>
#include <iostream>

namespace Gauss {
    class Equation {
    public:
        std::vector<std::int64_t> coefficients = {};
        std::int64_t result = 0;

        Equation() {}
        Equation(std::vector<std::int64_t> coefficients, std::int64_t result) : coefficients(coefficients), result(result) {}

        bool IsSolved();
        std::vector<std::vector<std::int64_t>> GetPossibleSolutions(std::vector<std::int64_t>& maximums);
        void GetPossibleSolutions(std::vector<std::int64_t>& inputsSoFar, std::vector<std::int64_t>& maximums, std::vector<std::vector<std::int64_t>>& solutions);
        bool TestSolution(std::vector<std::int64_t>& inputs);

        friend const Equation operator-(const Equation& first, const Equation& second) {
            Equation output{};
            for (int i = 0; i < first.coefficients.size(); i++) {
                output.coefficients.push_back(first.coefficients[i] - second.coefficients[i]);
            }
            output.result = first.result - second.result;
            return output;
        }

        friend const Equation operator*(const Equation& first, const std::int64_t& n) {
            Equation output{};
            for (int i = 0; i < first.coefficients.size(); i++) {
                output.coefficients.push_back(first.coefficients[i] == 0 ? 0 : first.coefficients[i] * n);
            }
            output.result = first.result == 0 ? 0 : first.result * n;
            return output;
        }

        friend const Equation operator/(const Equation& first, const std::int64_t& n) {
            return first * (1 / n);
        }

        friend std::ostream& operator<<(std::ostream& stream, const Equation& equation) {
            for (auto& v : equation.coefficients) {
                stream << v << "\t";
            }
            stream << equation.result;
            return stream;
        }
    };

    class System {
    public:
        std::vector<Equation> equations;
        System(std::vector<Equation> equations) : equations(equations) {}

        bool Reduce();
        void ReduceByColumn(int i);
        void ReduceRows();
        void PropogateRowReduction(int i);
        std::vector<std::vector<std::int64_t>> GetPossibleSolutions(std::vector<std::int64_t>& maximums);

        friend std::ostream& operator<<(std::ostream& stream, const System& system) {
            for (auto& equation : system.equations) {
                stream << equation << "\n";
            }
            return stream;
        }
    };
}