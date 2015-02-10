#include "../jtest.h"

/* String tests */
int test_string_alloc();
int test_string_free();
int test_string_const();
int test_string_substr();
int test_string_split();

/* List tests */
int test_list_alloc();
int test_list_free();
int test_list_append();
int test_list_length();

int main(int argc, char* argv[])
{
    TestCase_f tests[] = {
        /* String functions */
        &test_string_alloc,
        &test_string_free,
        &test_string_const,
        &test_string_substr,

        /* Linked List */
        &test_list_alloc,
        &test_list_free,
        &test_list_append,
        &test_list_length,

        /* End tests list with NULL */
        NULL,
    };
    return jtest_run(tests);
}
