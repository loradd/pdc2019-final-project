#include <iostream>
#include <random>
#include <chrono>

#include "bucketsort.hpp"

std::vector<int> generateInput(int size, int minValue, int maxValue) {
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> distribution(minValue, maxValue);
    std::vector<int> input = std::vector<int>();
    for (int i = 0; i < size; i++) {
        input.push_back(distribution(engine));
    }
    return input;
}   

void run_bucketsort_sequential(std::vector<int> input, int minValue, int maxValue) {
    auto start = std::chrono::high_resolution_clock::now();
    bucketsort_sequential(input, minValue, maxValue);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Bucketsort - Sequential: " << elapsed.count() << std::endl;
    assert(std::is_sorted(input.begin(), input.end()));
} 

int main(int argc, char **argv) {
    
    if (argc != 4) {
        std::cout << "Usage: main <input_size> <min_value> <max_value>" << std::endl;
        return EXIT_FAILURE;
    }
    
    int inputSize = atoi(argv[1]), 
        minValue = atoi(argv[2]), 
        maxValue = atoi(argv[3]);
    if (inputSize < 1) {
        std::cout << "Input size must be a positive integer" << std::endl;
        return EXIT_FAILURE;
    }
    if (minValue < 0) {
        std::cout << "Min value must be a positive integer" << std::endl;
        return EXIT_FAILURE;
    }  
    if (maxValue < minValue) {
        std::cout << "Max value must be greater than min vale" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<int> input = generateInput(inputSize, minValue, maxValue);
    run_bucketsort_sequential(input, minValue, maxValue);
    
    // run_bucketsort_openmp(input, minValue, maxValue);

    // run_bucketsort_openmpi(input, minValue, maxValue);

    // run_bucketsort_cuda(input, minValue, maxValue);

    return EXIT_SUCCESS;
}