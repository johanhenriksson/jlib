#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "error.h"
#include "array.h"

#define ARRAY_LIST_SIZE (10)

typedef struct array_list_t array_list_t;

struct array_list_t {
    int count;
    array_t* values;
};

error_t array_list_alloc(array_list_t**);
error_t array_list_free(array_list_t**);

error_t array_list_get(array_list_t*, int);

#endif
