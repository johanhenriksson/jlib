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

    if (count == 0 || index + count > source->length) 
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

error_t string_join(string_t* a, string_t* b, string_t** output) {
    return string_join_with(a, b, "", output);
}

error_t string_join_with(string_t* a, string_t* b, const char* spacing, string_t** output)
{
    THROW_NULL(a);
    THROW_NULL(b);
    THROW_NULL(output);
    *output = NULL;

    error_t e;
    string_t* c;

    size_t spacelen = strlen(spacing);
    size_t length = a->length + spacelen + b->length;

    /* Allocate space for the new string */
    e = string_alloc(&c, length); 
    THROW(e);

    /* Copy into new string */
    strncpy(c->ptr, a->ptr, a->length);
    strncpy(c->ptr + a->length, spacing, spacelen);
    strncpy(c->ptr + a->length + spacelen, b->ptr, b->length);
    c->length = length;
    
    *output = c;
    return E_SUCCESS;
}

error_t string_char_index(string_t* source, char needle, size_t* index)
{
    THROW_NULL(source);
    THROW_NULL(index);

    for(size_t i = 0; i < source->length; i++) {
        if (source->ptr[i] == needle) {
            *index = i;
            return E_SUCCESS;
        }
    }

    return E_NOT_FOUND;
}
