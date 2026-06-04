#pragma once

#include <Eigen/Dense>

#include <iosfwd>
#include <string>

using GaussMatrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using GaussVector = Eigen::VectorXd;

GaussMatrix load_csv_to_matrix(const std::string& filename);

void print_matrix_as_csv(std::ostream& out, const GaussMatrix& matrix, int precision = 10);

void print_vector_as_csv(std::ostream& out, const GaussVector& vector, int precision = 10);

bool vectors_are_close(const GaussVector& left, const GaussVector& right, double eps = 1e-8);
