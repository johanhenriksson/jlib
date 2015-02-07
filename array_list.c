#include "array_list.h"

error_t array_list_alloc(array_list_t** ptr)
{
    if (ptr == NULL)
        return E_NULL_PTR;
    *ptr = NULL;

    array_list_t* list = (array_list_t*)malloc(sizeof(array_list_t));
    if (list == NULL)
        return E_ALLOC_FAIL;

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
    if (ptr == NULL)
        return E_NULL_PTR;

    array_list_t* list = *ptr;
    if (list == NULL)
        return E_NULL_PTR;

    free(list->values);
    free(list);
    *ptr = NULL;

    return E_SUCCESS;
}

error_t array_list_append(array_list_t* list, void* value)
{
    if (list->count == list->values->length) {
        /* needs realloc */
        return -1;
    }

    error_t result = array_set(list->values, list->count++, value);
    THROW(result);

    return E_SUCCESS;

}
