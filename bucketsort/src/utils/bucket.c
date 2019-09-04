#include <stdlib.h>
#include <stdio.h>

#include "utils/bucket.h"

/// functions - create bucket
bucket_t *bucket_create() {
    bucket_t *bucket = malloc(sizeof(struct bucket));
    bucket -> size = 0;
    bucket -> head = NULL;
    return bucket;
}

/// functions - delete bucket
void bucket_delete(bucket_t *bucket) {
    if (bucket -> head != NULL) {
        element_delete(bucket -> head);
    }
    free(bucket);
}

/// functions - push element into bucket
void bucket_push(bucket_t *bucket, element_t *element) {
    if (element -> next != NULL) {
        element_delete(element -> next);
    }
    element -> next = bucket -> head;
    bucket -> head = element;
    bucket -> size = bucket -> size + 1;
}

/// functions - pop element from bucket
element_t *bucket_pop(bucket_t *bucket) {
    element_t *element = bucket -> head;
    if (element != NULL) {
        bucket -> head = element -> next;
        bucket -> size = bucket -> size - 1;
        element -> next = NULL;
    }
    return element;
}

/// functions - print bucket
void bucket_print(bucket_t *bucket) {
    printf("size: %d\n", bucket -> size);
    if (bucket -> head != NULL) {
        printf("next: "); 
        element_print(bucket -> head);
        printf("\n");
    }
}