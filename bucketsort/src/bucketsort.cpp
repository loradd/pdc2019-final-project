#include "bucketsort.hpp"

#include <algorithm>
#include "quicksort.hpp"

// bucketsort - sequential
void bucketsort_sequential(std::vector<int> &input, int minValue, int maxValue) {
    
    int bucketsNumber = maxValue - minValue + 1;
    std::vector<std::vector<int>> buckets(bucketsNumber);
    for (int inputIndex = 0; inputIndex < input.size(); inputIndex++) {
        int bucketIndex = input[inputIndex] - minValue;
        buckets[bucketIndex].push_back(input[inputIndex]);
    }

    for (int bucketIndex = 0; bucketIndex < buckets.size(); bucketIndex++) {
        // std::sort(buckets[bucketIndex].begin(), buckets[bucketIndex].end());
        quicksort_sequential(buckets[bucketIndex], 0, buckets[bucketIndex].size() - 1);
    }

    int inputIndex = 0;
    for (int bucketIndex = 0; bucketIndex < buckets.size(); bucketIndex++) {
        for (int elementIndex = 0; elementIndex < buckets[bucketIndex].size(); elementIndex++) {
            input[inputIndex++] = buckets[bucketIndex][elementIndex];
        }
    }

}