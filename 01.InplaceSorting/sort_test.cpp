#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "sorting.h"

template <typename SortFunction>
void check_sort(SortFunction sort_function, std::vector<int> data) {
    std::vector<int> expected = data;
    std::sort(expected.begin(), expected.end());

    sort_function(data.begin(), data.end());

    assert(data == expected);
}

void test_insertion_sort() {
    check_sort(insertion_sort<std::vector<int>::iterator>, {});
    check_sort(insertion_sort<std::vector<int>::iterator>, {42});
    check_sort(insertion_sort<std::vector<int>::iterator>, {1, 2, 3, 4, 5});
    check_sort(insertion_sort<std::vector<int>::iterator>, {5, 4, 3, 2, 1});
    check_sort(insertion_sort<std::vector<int>::iterator>, {3, 1, 2, 3, 2, 1});
    check_sort(insertion_sort<std::vector<int>::iterator>, {-5, -1, -10, 0, 3});
}

void test_heap_sort() {
    check_sort(heap_sort<std::vector<int>::iterator>, {});
    check_sort(heap_sort<std::vector<int>::iterator>, {42});
    check_sort(heap_sort<std::vector<int>::iterator>, {1, 2, 3, 4, 5});
    check_sort(heap_sort<std::vector<int>::iterator>, {5, 4, 3, 2, 1});
    check_sort(heap_sort<std::vector<int>::iterator>, {3, 1, 2, 3, 2, 1});
    check_sort(heap_sort<std::vector<int>::iterator>, {-5, -1, -10, 0, 3});
}

int main() {
    test_insertion_sort();
    test_heap_sort();

    std::cout << "All tests passed" << std::endl;

    return 0;
}
