#include <stdio.h>
#include <string.h>

#include "../jtest.h"
#include "../string.h"
#include "../error.h"

int test_string_alloc()
{
    error_t e;
    string_t* str = NULL;

    string_alloc(&str, 10);
    jassert_success("string_alloc() failed", e);
    jassert_not_null(str);
    jassert("Length does not equal 10", str->length == 10);

    return E_SUCCESS;
}

int test_string_free()
{
    error_t e;
    string_t* str = NULL;

    string_alloc(&str, 10);
    jassert_success("string_alloc() failed", e);

    string_free(&str);
    jassert_success("string_free() failed", e);
    jassert("String pointer should be null", str == NULL);

    return E_SUCCESS;
}

int test_string_const() 
{
    error_t e;
    string_t* str;

    e = string_const(&str, "hello");

    jassert_success("string_const() failed", e); 
    jassert("Length variable does not equal 5", str->length == 5);
    jassert("String does not equal hello", strncmp(str->ptr, "hello", 5) == 0);

    return E_SUCCESS;
}
