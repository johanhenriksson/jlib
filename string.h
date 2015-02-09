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

/* Alloc & dealloc */

error_t string_alloc(string_t**, size_t);
error_t string_free(string_t**);
error_t string_const(string_t**, const char*);

/* String operations */

error_t string_substr(string_t*, string_t**, size_t, size_t);
error_t string_split(string_t*, array_list_t**, char);
error_t string_join(string_t*, string_t*, string_t**);
error_t string_join_with(string_t*, string_t*, const char*, string_t**);
error_t string_char_index(string_t*, char, size_t*);

#endif
