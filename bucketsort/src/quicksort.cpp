#include "quicksort.hpp"

#include <iostream>

// utils - swap
void swap(std::vector<int> &input, int leftIndex, int rightIndex) {
    int leftValue = input[leftIndex];
    input[leftIndex] = input[rightIndex];
    input[rightIndex] = leftValue;
}

// utils - partition
int partition(std::vector<int> &input, int startIndex, int endIndex) {
    int pivot = input[endIndex];
    int leftIndex = startIndex - 1;
    for (int rightIndex = startIndex; rightIndex < endIndex; rightIndex++) {
        if (input[rightIndex] <= pivot) {
            leftIndex = leftIndex + 1;
            swap(input, leftIndex, rightIndex);
        }
    }
    swap(input, leftIndex + 1, endIndex);
    return leftIndex + 1;
}

// quicksort - sequential
void quicksort_sequential(std::vector<int> &input, int startIndex, int endIndex) {
    if (startIndex < endIndex) {
        int pivotIndex = partition(input, startIndex, endIndex);
        quicksort_sequential(input, startIndex, pivotIndex - 1);
        quicksort_sequential(input, pivotIndex + 1, endIndex);
    }
}