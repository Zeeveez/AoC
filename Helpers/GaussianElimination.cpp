#include <cmath>

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

    void Equation::Normalise() {


    }

    bool System::Solve() {
        for (int i = 0; i < std::min(equations.size(), equations[0].coefficients.size()); i++) {
            SolveColumn(i);
        }

        TryResolveRows();
        bool solved = true;
        for (auto& equation : equations) {
            if (!equation.IsSolved()) {
                solved = false;
            }
        }
        return solved;
    }

    void System::SolveColumn(int i) {
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

    void System::TryResolveRows() {
        for (int i = 0; i < equations.size(); i++) {
            if (equations[i].IsSolved()) {
                PropogateRowSolution(i);
            }
        }
    }

    void System::PropogateRowSolution(int i) {
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
}