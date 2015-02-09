#include <stdlib.h>
#include <stdio.h>

#include "../jtest.h"
#include "../error.h"
#include "../list.h"

int test_list_alloc()
{
    error_t e;
    list_t* list;

    e = list_alloc(&list);
    jassert_success("list_alloc() failed", e);
    jassert_null(list->node);
    jassert_null(list->next);

    free(list);
    return E_SUCCESS;
}

int test_list_free()
{
    error_t e;
    list_t* list;

    e = list_alloc(&list);
    jassert_success("list_alloc() failed", e);

    e = list_free(&list);
    jassert_success("list_alloc() failed", e);
    jassert_null(list);

    return E_SUCCESS;
}
