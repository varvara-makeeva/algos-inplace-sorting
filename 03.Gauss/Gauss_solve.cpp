#include "Gauss_solve.h"

#include <cmath>
#include <stdexcept>

GaussVector solve_gauss(const GaussMatrix& augmented_matrix) {
    const Eigen::Index rows = augmented_matrix.rows();
    const Eigen::Index cols = augmented_matrix.cols();

    if (rows == 0 || cols == 0) {
        throw std::runtime_error("Matrix is empty");
    }

    if (cols != rows + 1) {
        throw std::runtime_error("Augmented matrix must have n rows and n + 1 columns");
    }

    GaussMatrix matrix = augmented_matrix;
    const Eigen::Index n = rows;
    constexpr double eps = 1e-12;

    for (Eigen::Index column = 0; column < n; ++column) {
        Eigen::Index pivot_row = column;
        double max_abs_value = std::abs(matrix(column, column));

        for (Eigen::Index row = column + 1; row < n; ++row) {
            const double current_abs_value = std::abs(matrix(row, column));

            if (current_abs_value > max_abs_value) {
                max_abs_value = current_abs_value;
                pivot_row = row;
            }
        }

        if (max_abs_value < eps) {
            throw std::runtime_error("System has no unique solution");
        }

        if (pivot_row != column) {
            matrix.row(column).swap(matrix.row(pivot_row));
        }

        const double pivot = matrix(column, column);
        matrix.row(column) = matrix.row(column) / pivot;

        for (Eigen::Index row = column + 1; row < n; ++row) {
            const double factor = matrix(row, column);
            matrix.row(row) = matrix.row(row) - factor * matrix.row(column);
        }
    }

    GaussVector answer(n);

    for (Eigen::Index row = n - 1; row >= 0; --row) {
        double value = matrix(row, n);

        for (Eigen::Index column = row + 1; column < n; ++column) {
            value -= matrix(row, column) * answer(column);
        }

        answer(row) = value;

        if (row == 0) {
            break;
        }
    }

    return answer;
}
