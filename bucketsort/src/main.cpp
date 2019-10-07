#include <iostream>
#include <random>
#include <chrono>
#include <assert.h>
#include <algorithm>

#include "bucketsort.hpp"

std::vector<int> input_generate(int input_size, int input_min, int input_max) {
    std::random_device device;
    std::mt19937 engine(device());
    std::uniform_int_distribution<int> distribution(input_min, input_max);
    std::vector<int> input = std::vector<int>();
    for (int input_index = 0; input_index < input_size; input_index++) {
        input.push_back(distribution(engine));
    }
    return input;
}   

void run_bucketsort_sequential(std::vector<int> input, int input_min, int input_max, int buckets_number) {
    auto start = std::chrono::high_resolution_clock::now();
    bucketsort_sequential(input, input_min, input_max, buckets_number);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "bucketsort - sequential: " << elapsed.count() << std::endl;
    assert(std::is_sorted(input.begin(), input.end()));
} 

void run_bucketsort_omp(std::vector<int> input, int input_min, int input_max, int buckets_number) {
    auto start = std::chrono::high_resolution_clock::now();
    bucketsort_omp(input, input_min, input_max, buckets_number);
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "bucketsort - omp: " << elapsed.count() << std::endl;
    assert(std::is_sorted(input.begin(), input.end()));
}

int main(int argc, char **argv) {
    
    if (argc != 5) {
        std::cout << "Usage: main <input_size> <min_value> <max_value> <buckets_number>" << std::endl;
        return EXIT_FAILURE;
    }
    
    int input_size = atoi(argv[1]), 
        input_min = atoi(argv[2]), 
        input_max = atoi(argv[3]),
        buckets_number = atoi(argv[4]);

    if (input_size < 1) {
        std::cout << "Input size must be a positive integer" << std::endl;
        return EXIT_FAILURE;
    }
    if (input_min < 0) {
        std::cout << "Min value must be a positive integer" << std::endl;
        return EXIT_FAILURE;
    }  
    if (input_max < input_min) {
        std::cout << "Max value must be greater than min vale" << std::endl;
        return EXIT_FAILURE;
    }
    if (buckets_number < 1) {
        std::cout << "Buckets number must be greater than zero" << std::endl;
        return EXIT_FAILURE;
    } 

    std::vector<int> input = input_generate(input_size, input_min, input_max);
    
    run_bucketsort_sequential(input, input_min, input_max, buckets_number);
    run_bucketsort_omp(input, input_min, input_max, buckets_number);

    return EXIT_SUCCESS;
}