#include <stdlib.h>
#include <stdio.h>

#include "utils/element.h"

/// functions - create element
element_t *element_create(value_t value) {
    element_t *element = malloc(sizeof(struct element));
    element -> value = value;
    element -> next = NULL;
    return element;
}

/// functions - delete element
void element_delete(element_t *element) {
    if (element -> next != NULL) {
        element_delete(element -> next);
    }
    free(element);
}

/// functions - print element
void element_print(element_t *element) {
    printf("(value: %d)", element -> value);
    if (element -> next != NULL) {
        printf(" -> ");
        element_print(element -> next);
    }
}