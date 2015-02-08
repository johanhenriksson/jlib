#include <string.h>

#include "string.h"

error_t string_alloc(string_t** ptr, size_t length) 
{
    THROW_NULL(ptr);
    *ptr = NULL;

    string_t* string = (string_t*)malloc(sizeof(string_t) + length + 1);
    string->length = length;

    *ptr = string;
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
error_t string_const(string_t** ptr, const char* value) 
{
    THROW_NULL(ptr);
    *ptr = NULL;

    error_t r;
    string_t* string;

    size_t length = strlen(value);
    r = string_alloc(&string, length);
    THROW(r);

    strcpy(string->ptr, value);
    string->ptr[length] = '\0';

    *ptr = string;
    return E_SUCCESS;
}

error_t string_copy(string_t* source, string_t** dest) 
{
    THROW_NULL(source);
    THROW_NULL(dest);
    *dest = NULL;

    error_t e;
    string_t* string;
    e = string_alloc(&string, source->length);
    THROW(e);

    strncpy(string->ptr, source->ptr, source->length);
    string->ptr[source->length] = '\0';

    *dest = string;
    return E_SUCCESS;
}

error_t string_substr(string_t* source, string_t** dest, size_t index, size_t count)
{
    THROW_NULL(source);
    THROW_NULL(dest);
    *dest = NULL;

    if (index + count > source->length) 
        return E_BOUNDS;

    error_t r;
    string_t* substr;

    r = string_alloc(&substr, count);
    THROW(r);

    char* src_ptr = source->ptr + index;
    strncpy(substr->ptr, src_ptr, count);
    substr->ptr[count] = '\0';

    *dest = substr;
    return E_SUCCESS;
}

error_t string_split(string_t* source, array_list_t** output, char split)
{
    THROW_NULL(source);
    THROW_NULL(output);
    *output = NULL;

    error_t r;
    array_list_t* list;
    r = array_list_alloc(&list);
    THROW(r);

    size_t cut = 0;
    size_t len = 0;
    size_t idx = 1;
    string_t* element;
    for(idx = 1; idx < source->length; idx++) 
    {
        if (source->ptr[idx] == split) {
            r = string_substr(source, &element, cut, idx - cut);
            if (r != E_SUCCESS) 
                goto substr_error;
            array_list_append(list, element);
            idx++; /* skip split char */
            cut = idx;
        }
    }

    /* grab the last element (if any) */
    if (idx > cut) {
        r = string_substr(source, &element, cut, idx - cut);
        if (r != E_SUCCESS) 
            goto substr_error;
        array_list_append(list, element);
    }

    *output = list;
    return E_SUCCESS;

    /* cleanup used memory on failure */
substr_error:
    for(int i = 0; i < list->count; i++) 
        string_free(list->values->ptr[i]);
    array_list_free(&list);
    return r;
}
