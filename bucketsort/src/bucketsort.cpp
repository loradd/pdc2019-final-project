#include <algorithm>
#include <assert.h>

#include "omp.h"
#include "bucketsort.hpp"
#include "quicksort.hpp"

#include <iostream>

void merge (std::vector<std::vector<int>> &out, std::vector<std::vector<int>> &in) {
    assert(out.size() == in.size());    
    for (int index = 0; index < out.size(); index++) {
        out[index].insert(out[index].end(), in[index].begin(), in[index].end());
    }
}

#pragma omp declare reduction(merge:std::vector<std::vector<int>>:\
    merge(omp_out, omp_in)) initializer(omp_priv(omp_orig))

// bucketsort - sequential
void bucketsort_sequential(std::vector<int> &input, int input_min, int input_max, int buckets_number) {
    int buckets_range = (input_max - input_min + buckets_number) / buckets_number;
    std::vector<std::vector<int>> buckets(buckets_number);
    // distribute
    for (int input_index = 0; input_index < input.size(); input_index++)
        buckets[(input[input_index] - input_min) / buckets_range].push_back(input[input_index]);    
    // sort
    for (int buckets_index = 0; buckets_index < buckets_number; buckets_index++)
        if (buckets[buckets_index].size() > 1) 
            std::sort(buckets[buckets_index].begin(), buckets[buckets_index].end());
            // quicksort_sequential(buckets[buckets_index], 0, buckets[buckets_index].size() - 1);
    // merge
    int input_index = 0;
    for (int buckets_index = 0; buckets_index < buckets_number; buckets_index++) {
        for (int elements_index = 0; elements_index < buckets[buckets_index].size(); elements_index++) {
            input[input_index++] = buckets[buckets_index][elements_index];
        }
    }
}

// bucketsort - omp
void bucketsort_omp(std::vector<int> &input, int input_min, int input_max, int buckets_number) {
    int buckets_range = (input_max - input_min + buckets_number) / buckets_number;
    std::vector<std::vector<int>> buckets(buckets_number);
    #pragma omp parallel num_threads(omp_get_num_procs()) \
        default(none) shared(input, input_min, buckets, buckets_number, buckets_range)
    {   
        // distribute
        #pragma omp for reduction(merge:buckets) schedule(static)
        for (int input_index = 0; input_index < input.size(); input_index++)
            buckets[(input[input_index] - input_min) / buckets_range].push_back(input[input_index]);    
        // sort
        #pragma omp for schedule(dynamic)
        for (int buckets_index = 0; buckets_index < buckets_number; buckets_index++)
            if (buckets[buckets_index].size() > 1)
                std::sort(buckets[buckets_index].begin(), buckets[buckets_index].end());
                // quicksort_sequential(buckets[buckets_index], 0, buckets[buckets_index].size() - 1)
    }
    // merge
    int input_index = 0;
    for (int buckets_index = 0; buckets_index < buckets_number; buckets_index++) {
        for (int elements_index = 0; elements_index < buckets[buckets_index].size(); elements_index++) {
            input[input_index++] = buckets[buckets_index][elements_index];
        }
    }
}