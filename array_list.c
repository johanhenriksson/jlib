#include <stdlib.h>
#include <stdio.h>

#include "array_list.h"

error_t array_list_alloc(array_list_t** ptr)
{
    THROW_NULL(ptr);
    *ptr = NULL;

    array_list_t* list = (array_list_t*)malloc(sizeof(array_list_t));
    THROW_ALLOC(list);

    /* allocate dynamic array */
    error_t result;
    array_t* values;
    result = array_alloc(&values, ARRAY_LIST_SIZE);
    if (result != E_SUCCESS) {
        free(list);
        return result;
    }

    list->values = values;
    list->count = 0;
    *ptr = list;

    return E_SUCCESS;
}

error_t array_list_free(array_list_t** ptr)
{
    THROW_NULL(ptr);

    array_list_t* list = *ptr;
    THROW_NULL(list);

    free(list->values);
    free(list);
    *ptr = NULL;

    return E_SUCCESS;
}

error_t array_list_get(array_list_t* list, int index, void** value)
{
    THROW_NULL(list);
    THROW_BOUNDS(index, 0, list->count);

    *value = list->values->ptr[index];

    return E_SUCCESS;
}

error_t array_list_append(array_list_t* list, void* value)
{
    /* check if array needs realloc */
    if (list->count == list->values->length) {
        error_t result = array_realloc(&list->values, list->values->length * 2);
        THROW(result);
    }

    error_t result = array_set(list->values, list->count++, value);
    THROW(result);

    return E_SUCCESS;
}

error_t array_list_index(array_list_t* list, void* value, int* index) 
{
    THROW_NULL(list);

    void* ptr;
    for(int i = 0; i < list->count; i++) {
        ptr = list->values->ptr[i];
        if (ptr == value) {
            *index = i;
            return E_SUCCESS;
        }
    }

    *index = -1;
    return E_NOT_FOUND;
}

