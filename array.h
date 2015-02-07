#ifndef ARRAY_H
#define ARRAY_H

#include "error.h"

/* not really sure about this */
#define array_foreach(var_name, array_obj) void* var_name = array_obj->ptr[0]; for(int _array_idx = 0; _array_idx < array_obj->length; var_name = array_obj->ptr[++_array_idx])

/* dynamic array with bounds checking */

typedef struct array_t array_t;

struct array_t {
    int length;
    void* ptr[];
};

error_t array_alloc(array_t**, int);
error_t array_realloc(array_t**, int);
error_t array_free(array_t**);

error_t array_set(array_t*, int, void*);
error_t array_get(array_t*, int, void**);
error_t array_clear(array_t*);

#endif
