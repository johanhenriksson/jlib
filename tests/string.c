#include <stdio.h>
#include <string.h>

#include "../jtest.h"
#include "../string.h"
#include "../error.h"

int test_string_alloc()
{
    error_t e;
    string_t* str = NULL;

    e = string_alloc(&str, 10);
    jassert_success("string_alloc() failed", e);
    jassert_not_null(str);
    jassert("Length does not equal 10", str->length == 10);

    free(str);
    return E_SUCCESS;
}

int test_string_free()
{
    error_t e;
    string_t* str = NULL;

    e = string_alloc(&str, 10);
    jassert_success("string_alloc() failed", e);

    e = string_free(&str);
    jassert_success("string_free() failed", e);
    jassert_null(str);

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

    string_free(&str);
    return E_SUCCESS;
}

int test_string_substr()
{
    error_t e;
    string_t* source;

    e = string_const(&source, "hello world");
    jassert_success("string_cont() failed", e);

    string_t* sub = NULL;

    e = string_substr(source, &sub, 0, 100);
    jassert_error("Bounds error expected", e, E_BOUNDS);
    jassert_null(sub);

    e = string_substr(source, &sub, 100, 1);
    jassert_error("Bounds error expected", e, E_BOUNDS);
    jassert_null(sub);

    e = string_substr(source, &sub, 0, 0);
    jassert_error("Bounds error expected", e, E_BOUNDS);
    jassert_null(sub);

    e = string_substr(source, &sub, 6, 5);
    jassert_success("string_substr() failed", e);
    jassert_not_null(sub);
    jassert_not_null(sub->ptr);
    jassert("Expected length to be 5", sub->length == 5);
    jassert("Expected string to equal world", strncmp(sub->ptr, "world", 5) == 0);

    string_free(&sub);
    string_free(&source);

    return E_SUCCESS;
}
