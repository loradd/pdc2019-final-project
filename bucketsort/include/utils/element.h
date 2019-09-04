#ifndef __ELEMENT_H__
#define __ELEMENT_H__

/// types - value
typedef int value_t;

/// types - element
typedef struct element element_t;
struct element {
    value_t value;
    element_t *next;
};

/// functions - create element
element_t *element_create(value_t value);

/// functions - delete element
void element_delete(element_t *element); 

/// functions - print element
void element_print(element_t *element);

#endif