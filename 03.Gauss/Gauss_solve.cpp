#include "Gauss_solve.h"

#include <cmath>
#include <stdexcept>

GaussVector Gauss_solve(GaussMatrix& ab) {
    const Eigen::Index rows = ab.rows();
    const Eigen::Index cols = ab.cols();

    if (rows == 0 || cols == 0) {
        throw std::runtime_error("Matrix is empty");
    }

    if (cols != rows + 1) {
        throw std::runtime_error("Augmented matrix must have n rows and n + 1 columns");
    }

    const Eigen::Index n = rows;
    constexpr double eps = 1e-12;

    for (Eigen::Index column = 0; column < n; ++column) {
        Eigen::Index pivot_row = column;
        double max_abs_value = std::abs(ab(column, column));

        for (Eigen::Index row = column + 1; row < n; ++row) {
            const double current_abs_value = std::abs(ab(row, column));

            if (current_abs_value > max_abs_value) {
                max_abs_value = current_abs_value;
                pivot_row = row;
            }
        }

        if (max_abs_value < eps) {
            throw std::runtime_error("System has no unique solution");
        }

        if (pivot_row != column) {
            ab.row(column).swap(ab.row(pivot_row));
        }

        const double pivot = ab(column, column);
        ab.row(column) = ab.row(column) / pivot;

        for (Eigen::Index row = column + 1; row < n; ++row) {
            const double factor = ab(row, column);
            ab.row(row) = ab.row(row) - factor * ab.row(column);
        }
    }

    GaussVector answer(n);

    for (Eigen::Index row = n - 1; row >= 0; --row) {
        double value = ab(row, n);

        for (Eigen::Index column = row + 1; column < n; ++column) {
            value -= ab(row, column) * answer(column);
        }

        answer(row) = value;

        if (row == 0) {
            break;
        }
    }

    return answer;
}
