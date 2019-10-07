#include "quicksort.hpp"

#include <omp.h>
#include <iostream>

// utils - swap
void swap(std::vector<int> &input, int input_left, int input_right) {
    int input_temp = input[input_left];
    input[input_left] = input[input_right];
    input[input_right] = input_temp;
}

// utils - partition
int partition(std::vector<int> &input, int input_start, int input_end) {
    int input_pivot = input[input_end];
    int input_left = input_start - 1;
    for (int input_right = input_start; input_right < input_end; input_right++) {
        if (input[input_right] <= input_pivot) {
            input_left = input_left + 1;
            swap(input, input_left, input_right);
        }
    }
    swap(input, input_left + 1, input_end);
    return input_left + 1;
}

// quicksort - sequential
void quicksort_sequential(std::vector<int> &input, int input_start, int input_end) {
    if (input_start < input_end) {
        int input_pivot = partition(input, input_start, input_end);
        quicksort_sequential(input, input_start, input_pivot - 1);
        quicksort_sequential(input, input_pivot + 1, input_end);
    }
}

// quicksort - omp
void quicksort_omp(std::vector<int> &input, int input_start, int input_end) {
    if (input_start < input_end) {
        int input_pivot = partition(input, input_start, input_end);
        #pragma omp task shared(input) firstprivate(input_start, input_pivot)
        { quicksort_omp(input, input_start, input_pivot - 1); }
        #pragma omp task shared(input) firstprivate(input_end, input_pivot)
        { quicksort_omp(input, input_pivot + 1, input_end); }
    }
}