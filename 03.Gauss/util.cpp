#include "util.h"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

GaussMatrix load_csv_to_matrix(const std::string& filename) {
    std::ifstream input(filename);

    if (!input.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<std::vector<double>> rows;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<double> row;
        std::stringstream line_stream(line);
        std::string cell;

        while (std::getline(line_stream, cell, ',')) {
            row.push_back(std::stod(cell));
        }

        if (!rows.empty() && row.size() != rows.front().size()) {
            throw std::runtime_error("CSV rows have different sizes");
        }

        rows.push_back(row);
    }

    if (rows.empty()) {
        throw std::runtime_error("CSV file is empty");
    }

    GaussMatrix matrix(static_cast<Eigen::Index>(rows.size()),
                       static_cast<Eigen::Index>(rows.front().size()));

    for (Eigen::Index i = 0; i < matrix.rows(); ++i) {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j) {
            matrix(i, j) = rows[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix& matrix, int precision) {
    out << std::fixed << std::setprecision(precision);

    for (Eigen::Index i = 0; i < matrix.rows(); ++i) {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j) {
            if (j > 0) {
                out << ',';
            }

            out << matrix(i, j);
        }

        out << '\n';
    }
}

void print_vector_as_csv(std::ostream& out, const GaussVector& vector, int precision) {
    out << std::fixed << std::setprecision(precision);

    for (Eigen::Index i = 0; i < vector.size(); ++i) {
        if (i > 0) {
            out << ',';
        }

        out << vector(i);
    }

    out << '\n';
}

bool vectors_are_close(const GaussVector& left, const GaussVector& right, double eps) {
    if (left.size() != right.size()) {
        return false;
    }

    for (Eigen::Index i = 0; i < left.size(); ++i) {
        if (std::abs(left(i) - right(i)) > eps) {
            return false;
        }
    }

    return true;
}
