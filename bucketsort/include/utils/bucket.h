#ifndef __BUCKET_H__
#define __BUCKET_H__

#include "utils/element.h"

/// types - bucket
typedef struct bucket bucket_t;
struct bucket {
    int size;
    element_t *head;
};

/// functions - create bucket
bucket_t *bucket_create();

/// functions - delete bucket
void bucket_delete();

/// functions - push bucket element
void bucket_push(bucket_t *bucket, element_t *element);

/// functions - pop bucket element
element_t *bucket_pop(bucket_t *bucket);

/// functions - print bucket
void bucket_print(bucket_t *bucket);

#endif