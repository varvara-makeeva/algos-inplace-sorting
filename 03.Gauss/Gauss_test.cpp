#include "Gauss_solve.h"
#include "util.h"

#include <Eigen/Dense>

#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>

void require(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "Test failed: " << message << '\n';
        std::exit(1);
    }
}

void test_two_by_two_system() {
    GaussMatrix matrix(2, 3);
    matrix << 2, 1, 5,
              1, -1, 1;

    GaussVector expected(2);
    expected << 2, 1;

    const GaussVector result = Gauss_solve(matrix);

    require(vectors_are_close(result, expected), "2x2 system");
}

void test_three_by_three_system() {
    GaussMatrix matrix(3, 4);
    matrix << 2, 1, -1, 8,
             -3, -1, 2, -11,
             -2, 1, 2, -3;

    GaussVector expected(3);
    expected << 2, 3, -1;

    const GaussVector result = Gauss_solve(matrix);

    require(vectors_are_close(result, expected), "3x3 system");
}

void test_identity_matrix() {
    GaussMatrix matrix(3, 4);
    matrix << 1, 0, 0, 4,
              0, 1, 0, -2,
              0, 0, 1, 7;

    GaussVector expected(3);
    expected << 4, -2, 7;

    const GaussVector result = Gauss_solve(matrix);

    require(vectors_are_close(result, expected), "identity matrix");
}

void test_diagonal_matrix() {
    GaussMatrix matrix(3, 4);
    matrix << 2, 0, 0, 10,
              0, -4, 0, 8,
              0, 0, 5, 15;

    GaussVector expected(3);
    expected << 5, -2, 3;

    const GaussVector result = Gauss_solve(matrix);

    require(vectors_are_close(result, expected), "diagonal matrix");
}

void test_large_reproducible_random_system() {
    constexpr int size = 40;

    std::mt19937 generator(42);
    std::uniform_real_distribution<double> distribution(-10.0, 10.0);

    GaussMatrix a(size, size);
    GaussVector expected(size);

    for (int i = 0; i < size; ++i) {
        expected(i) = distribution(generator);

        for (int j = 0; j < size; ++j) {
            a(i, j) = distribution(generator);
        }

        a(i, i) += 100.0;
    }

    const GaussVector b = a * expected;

    GaussMatrix augmented(size, size + 1);
    augmented.leftCols(size) = a;
    augmented.col(size) = b;

    const GaussVector result = Gauss_solve(augmented);

    require(vectors_are_close(result, expected, 1e-7), "large reproducible random system");
}

void test_wrong_matrix_size() {
    GaussMatrix matrix(2, 2);
    matrix << 1, 2,
              3, 4;

    bool exception_was_thrown = false;

    try {
        Gauss_solve(matrix);
    } catch (const std::runtime_error&) {
        exception_was_thrown = true;
    }

    require(exception_was_thrown, "wrong matrix size");
}

int main() {
    test_two_by_two_system();
    test_three_by_three_system();
    test_identity_matrix();
    test_diagonal_matrix();
    test_large_reproducible_random_system();
    test_wrong_matrix_size();

    std::cout << "All Gauss tests passed\n";
    return 0;
}
