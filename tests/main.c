#include "../jtest.h"

int test_string_alloc();
int test_string_free();
int test_string_const();

int main(int argc, char* argv[])
{
    TestCase_f tests[] = {
        &test_string_alloc,
        &test_string_free,
        &test_string_const,
        NULL,
    };
    jtest_run(tests);
}
