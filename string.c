#include <string.h>

#include "string.h"

error_t string_alloc(string_t** ptr, size_t length) 
{
    THROW_NULL(ptr);
    *ptr = NULL;

    string_t* string = (string_t*)malloc(sizeof(string_t) + length + 1);
    string->length = length;

    return E_SUCCESS;
}

error_t string_free(string_t** ptr) 
{
    THROW_NULL(ptr);
    
    string_t* string = *ptr;
    THROW_NULL(string);

    free(string->ptr);
    free(string);
    *ptr = NULL;

    return E_SUCCESS;
}

/** Allocates a new string from a string constant */
error_t string_const(string** ptr, const char* value) 
{
    THROW_NULL(ptr);
    *ptr = NULL;

    error_t r;
    string_t* string;

    r = string_alloc(&string, strlen(value));
    THROW(r);

    strcpy(string->ptr, value);

    *ptr = string;
    return E_SUCCESS;
}
