#include <stdlib.h>
#include "array.h"

error_t array_alloc(array_t** ptr, int length)
{
    THROW_NULL(ptr);
    *ptr = NULL;

    size_t size = sizeof(array_t) + length * sizeof(void*);

    array_t* array = (array_t*)malloc(size);
    THROW_ALLOC(array);

    array->length = length;
    *ptr = array;

    return E_SUCCESS;
}

error_t array_realloc(array_t** ptr, int length)
{
    THROW_NULL(ptr);

    size_t size = sizeof(array_t) + length * sizeof(void*);
    array_t* array = (array_t*)realloc(*ptr, size);
    THROW_ALLOC(array);

    array->length = length;
    *ptr = array;

    return E_SUCCESS;
}

error_t array_free(array_t** ptr)
{
    THROW_NULL(ptr);

    array_t* array = *ptr;
    THROW_NULL(ptr);

    free(array);
    *ptr = NULL;

    return E_SUCCESS;
}

error_t array_get(array_t* array, int index, void** value)
{
    THROW_NULL(array);
    THROW_NULL(value);
    THROW_BOUNDS(index, 0, array->length);

    *value = array->ptr[index];
    return E_SUCCESS;
}

error_t array_set(array_t* array, int index, void* value)
{
    THROW_NULL(array);
    THROW_BOUNDS(index, 0, array->length);

    array->ptr[index] = value;
    return E_SUCCESS;
}

error_t array_clear(array_t* array)
{
    THROW_NULL(array);

    for(int i = 0; i < array->length; i++) 
        array->ptr[i] = NULL;

    return E_SUCCESS;
}
