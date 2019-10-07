#ifndef __BUCKETSORT_HPP__
#define __BUCKETSORT_HPP__

#include <vector>

// bucketsort - sequential
void bucketsort_sequential(std::vector<int> &input, int input_min, int input_max, int buckets_number);

// bucketsort - omp
void bucketsort_omp(std::vector<int> &input, int input_min, int input_max, int buckets_number);


#endif