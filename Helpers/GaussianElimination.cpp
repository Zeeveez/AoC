#include <cmath>
#include <algorithm>

#include "GaussianElimination.h"

namespace Gauss {
    bool Equation::IsSolved() {
        int idx = -1;
        for (int i = 0; i < coefficients.size(); i++) {
            if (coefficients[i] != 0) {
                if (idx != -1) {
                    return false;
                }
                idx = i;
            }
        }
        if (idx == -1) {
            return true;
        }

        auto scalingFactor = coefficients[idx];
        for (int i = idx; i < coefficients.size(); i++) {
            coefficients[i] /= coefficients[i] == 0 ? 1 : scalingFactor;
        }
        result /= result == 0 ? 1 : scalingFactor;

        return true;
    }

    std::vector<std::vector<std::int64_t>> Equation::GetPossibleSolutions(std::vector<std::int64_t>& maximums) {
        std::vector<std::int64_t> inputs = {};
        std::vector<std::vector<std::int64_t>> solutions = {};
        GetPossibleSolutions(inputs, maximums, solutions);
        return solutions;
    }

    void Equation::GetPossibleSolutions(std::vector<std::int64_t>& inputsSoFar, std::vector<std::int64_t>& maximums, std::vector<std::vector<std::int64_t>>& solutions) {
        if (inputsSoFar.size() == coefficients.size()) {
            if (TestSolution(inputsSoFar)) { solutions.push_back(inputsSoFar); }
            return;
        }

        if (coefficients[inputsSoFar.size()] == 0) {
            inputsSoFar.push_back(0);
            GetPossibleSolutions(inputsSoFar, maximums, solutions);
            inputsSoFar.pop_back();
        }
        else {
            for (int j = 0; j <= maximums[inputsSoFar.size()]; j++) {
                inputsSoFar.push_back(j);
                GetPossibleSolutions(inputsSoFar, maximums, solutions);
                inputsSoFar.pop_back();
            }
        }
    }

    bool Equation::TestSolution(std::vector<std::int64_t>& inputs) {
        std::int64_t result = 0;
        for (int i = 0; i < inputs.size(); i++) {
            result += inputs[i] * coefficients[i];
        }
        return result == this->result;
    }

    bool System::Reduce() {
        for (int i = 0; i < std::min(equations.size(), equations[0].coefficients.size()); i++) {
            ReduceByColumn(i);
        }

        ReduceRows();
        bool solved = true;
        for (auto& equation : equations) {
            if (!equation.IsSolved()) {
                solved = false;
            }
        }
        return solved;
    }

    void System::ReduceByColumn(int i) {
        bool found = false;
        for (auto row = i; row < equations.size(); row++) {
            if (equations[row].coefficients[i] != 0) {
                if (row != i) {
                    std::swap(equations[row], equations[i]);
                }
                if (equations[row].coefficients[i] < 0) {
                    equations[row] = equations[row] * -1;
                }
                found = true;
                break;
            }
        }
        if (!found) { return; }

        // Solve cells below
        for (int row = i + 1; row < equations.size(); row++) {
            if (equations[row].coefficients[i] != 0) {
                equations[row] =
                    equations[row] * equations[i].coefficients[i]
                    - equations[i] * equations[row].coefficients[i];
            }
        }

        // Solve cells above
        for (int row = i - 1; row > -1; row--) {
            if (equations[row].coefficients[i] != 0) {
                equations[row] =
                    equations[row] * equations[i].coefficients[i]
                    - equations[i] * equations[row].coefficients[i];
            }
        }
    }

    void System::ReduceRows() {
        for (int i = 0; i < equations.size(); i++) {
            if (equations[i].IsSolved()) {
                PropogateRowReduction(i);
            }
        }
    }

    void System::PropogateRowReduction(int i) {
        int solvedColumn = -1;
        for (int k = 0; k < equations[i].coefficients.size(); k++) {
            if (equations[i].coefficients[k] == 1) {
                solvedColumn = k;
                break;
            }
        }
        if (solvedColumn == -1) { return; }

        for (int j = 0; j < equations.size(); j++) {
            if (j == i) { continue; }
            if (equations[j].coefficients[i] != 0 && equations[i].coefficients[i] != 0) {
                equations[j] =
                    equations[j] * equations[i].coefficients[i]
                    - equations[i] * equations[j].coefficients[i];
                equations[j].IsSolved();
                equations[i].IsSolved();
            }
        }
    }

    std::vector<std::vector<std::int64_t>> System::GetPossibleSolutions(std::vector<std::int64_t>& maximums) {
        std::sort(
            equations.begin(), equations.end(),
            [](const Equation& a, const Equation& b) {
                int aNonZeroCos = 0;
                int bNonZeroCos = 0;
                for (int co = 0; co < a.coefficients.size(); co++) {
                    aNonZeroCos += a.coefficients[co] != 0;
                    bNonZeroCos += b.coefficients[co] != 0;
                }
                return std::abs(aNonZeroCos) < std::abs(bNonZeroCos);

            }
        );

        std::vector<std::vector<std::int64_t>> possibleSolutions = {};
        int first = 0;
        for (int i = 0; i < equations.size(); i++) {
            bool hasCoefficients = false;
            for (int co = 0; co < equations[first].coefficients.size(); co++) {
                hasCoefficients |= equations[i].coefficients[co] != 0;
            }
            if (!hasCoefficients) { continue; }
            possibleSolutions = equations[i].GetPossibleSolutions(maximums);
            first = i;
            break;
        }
        for (int i = first + 1; i < equations.size(); i++) {
            bool hasCoefficients = false;
            for (int co = 0; co < equations[first].coefficients.size(); co++) {
                hasCoefficients |= equations[i].coefficients[co] != 0;
            }
            if (!hasCoefficients) { continue; }
            std::vector<std::vector<std::int64_t>> newPossibleSolutions = equations[i].GetPossibleSolutions(maximums);
            std::vector<std::vector<std::int64_t>> possibleInBothSolutions = {};
            for (int j = 0; j < possibleSolutions.size(); j++) {
                for (int k = 0; k < newPossibleSolutions.size(); k++) {
                    bool good = true;
                    for (int co = 0; co < equations[first].coefficients.size(); co++) {
                        if (equations[first].coefficients[co] == 0 || equations[i].coefficients[co] == 0) { continue; }
                        if (possibleSolutions[j][co] != newPossibleSolutions[k][co]) {
                            good = false;
                            break;
                        }
                    }
                    if (good) {
                        std::vector<std::int64_t> newSolution = possibleSolutions[j];
                        for (int co = 0; co < possibleSolutions[j].size(); co++) {
                            if (newSolution[co] == 0) {
                                newSolution[co] = newPossibleSolutions[k][co];
                            }
                        }

                        bool stillValid = true;
                        for (int sol = 0; sol <= i; sol++) {
                            stillValid &= equations[sol].TestSolution(newSolution);
                            if (!stillValid) { break; }
                        }
                        if (stillValid) {
                            for (auto& existingSol : possibleInBothSolutions) {
                                for (int v = 0; v < existingSol.size(); v++) {
                                    if (existingSol[v] != newSolution[v]) {
                                        // different
                                        goto trynext;
                                    }
                                }
                                // same - don't add
                                goto skipadd;
                            trynext:;
                            }

                            possibleInBothSolutions.push_back(newSolution);
                        skipadd:;
                        }
                    }
                }
            }
            possibleSolutions = possibleInBothSolutions;
        }
        return possibleSolutions;
    }
}