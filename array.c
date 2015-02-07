#include <stdlib.h>
#include "array.h"

error_t array_alloc(array_t** ptr, int length)
{
    if (ptr == NULL)
        return E_NULL_PTR;
    *ptr = NULL;

    size_t size = sizeof(array_t) + length * sizeof(void*);

    array_t* array = (array_t*)malloc(size);
    if (array == NULL)
        return E_ALLOC_FAIL;

    array->length = length;
    *ptr = array;

    return E_SUCCESS;
}

error_t array_realloc(array_t** ptr, int length)
{
    if (ptr == NULL)
        return E_NULL_PTR;

    size_t size = sizeof(array_t) + length * sizeof(void*);

    array_t* array = (array_t*)realloc(*ptr, size);
    if (array == NULL)
        return E_ALLOC_FAIL;

    array->length = length;
    *ptr = array;

    return E_SUCCESS;
}

error_t array_free(array_t** ptr)
{
    if (ptr == NULL)
        return E_NULL_PTR;

    array_t* array = *ptr;
    if (array == NULL)
        return E_NULL_PTR;

    free(array);
    *ptr = NULL;

    return E_SUCCESS;
}

error_t array_get(array_t* array, int index, void** value)
{
    if (array == NULL || value == NULL)
        return E_NULL_PTR;

    if (index < 0 || index >= array->length)
        return E_BOUNDS;

    *value = array->ptr[index];
    return E_SUCCESS;
}

error_t array_set(array_t* array, int index, void* value)
{
    if (array == NULL)
        return E_NULL_PTR;

    if (index < 0 || index >= array->length)
        return E_BOUNDS;

    array->ptr[index] = value;
    return E_SUCCESS;
}

error_t array_clear(array_t* array)
{
    if (array == NULL)
        return E_NULL_PTR;

    for(int i = 0; i < array->length; i++) 
        array->ptr[i] = NULL;

    return E_SUCCESS;
}
