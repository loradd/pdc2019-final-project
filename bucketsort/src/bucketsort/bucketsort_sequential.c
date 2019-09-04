#include "utils/bucket.h"

int main() {

    bucket_t *bucket = bucket_create();

    element_t *first_element = element_create(1), 
              *second_element = element_create(2);

    bucket_push(bucket, first_element);
    bucket_print(bucket);

    bucket_push(bucket, second_element);
    bucket_print(bucket);

    first_element = bucket_pop(bucket);
    bucket_print(bucket);

    bucket_push(bucket, first_element);
    bucket_print(bucket);

    bucket_pop(bucket);
    bucket_print(bucket);

    bucket_delete(bucket);

    return 0;
}