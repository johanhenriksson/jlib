#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
 
#include "array_list.h"
#include "error.h"

typedef struct string_t string_t;

struct string_t {
    size_t length;
    char ptr[];
};

error_t string_alloc(string_t**, size_t);
error_t string_free(string_t**);
error_t string_const(string_t**, const char*);
error_t string_substr(string_t*, string_t**, size_t, size_t);
error_t string_split(string_t*, array_list_t**, char);

#endif
