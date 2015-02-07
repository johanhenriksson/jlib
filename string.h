#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
 
#include "error.h"

typedef struct string_t string_t;

struct string_t {
    size_t length;
    char ptr[];
};

error_t string_alloc(string_t**, size_t);

#endif
