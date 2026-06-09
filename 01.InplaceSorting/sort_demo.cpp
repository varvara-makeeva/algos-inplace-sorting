#include <algorithm>
#include <iostream>
#include <vector>

#include "sorting.h"

void print_vector(const std::vector<int>& data) {
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> original = {5, -1, 7, 3, 3, 0, -10, 8};

    std::vector<int> insertion_data = original;
    std::vector<int> heap_data = original;

    std::cout << "Original: ";
    print_vector(original);

    insertion_sort(insertion_data.begin(), insertion_data.end());
    heap_sort(heap_data.begin(), heap_data.end());

    std::cout << "Insertion sort: ";
    print_vector(insertion_data);

    std::cout << "Heap sort: ";
    print_vector(heap_data);

    std::cout << "Insertion correct: "
              << std::is_sorted(insertion_data.begin(), insertion_data.end()) << std::endl;

    std::cout << "Heap correct: " << std::is_sorted(heap_data.begin(), heap_data.end())
              << std::endl;

    return 0;
}
