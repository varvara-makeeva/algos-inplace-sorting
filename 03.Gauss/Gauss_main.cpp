#include "Gauss_solve.h"
#include "util.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    try {
        const std::string input_file = argc > 1 ? argv[1] : "AB.csv";

        const GaussMatrix augmented_matrix = load_csv_to_matrix(input_file);
        const GaussVector solution = solve_gauss(augmented_matrix);

        print_vector_as_csv(std::cout, solution);

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
