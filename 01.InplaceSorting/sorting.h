#ifndef SORTING_H
#define SORTING_H

#include <cstddef>
#include <utility>

template <typename Iterator>
void insertion_sort(Iterator begin, Iterator end)
{
    for (Iterator i = begin; i != end; ++i) {
        Iterator j = i;
        while (j != begin && *j < *(j - 1)) {
            using std::swap;
            swap(*j, *(j - 1));
            --j;
        }
    }
}

template <typename Iterator>
void heapify(Iterator begin, std::size_t heap_size, std::size_t root)
{
    std::size_t largest = root;
    std::size_t left = 2 * root + 1;
    std::size_t right = 2 * root + 2;

    if (left < heap_size && *(begin + largest) < *(begin + left)) {
        largest = left;
    }

    if (right < heap_size && *(begin + largest) < *(begin + right)) {
        largest = right;
    }

    if (largest != root) {
        using std::swap;
        swap(*(begin + root), *(begin + largest));
        heapify(begin, heap_size, largest);
    }
}

template <typename Iterator>
void heap_sort(Iterator begin, Iterator end)
{
    std::size_t n = end - begin;

    if (n < 2) {
        return;
    }

    for (std::size_t i = n / 2; i > 0; --i) {
        heapify(begin, n, i - 1);
    }

    for (std::size_t i = n - 1; i > 0; --i) {
        using std::swap;
        swap(*begin, *(begin + i));
        heapify(begin, i, 0);
    }
}

#endif
