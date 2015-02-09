#include <stdlib.h>
#include <stdio.h>

#include "jtest.h"

int jtest_asserts = 0;
int jtest_tests   = 0;

int jtest_run(TestCase_f* tests) 
{
    int error;
    jtest_tests   = 0;
    jtest_asserts = 0;

    printf("\n** Running jtest **\n\n");

    for(int t = 0; ; t++)
    {
        TestCase_f test_func = tests[t];
        if (test_func == NULL)
            break;

        error = test_func(); 
        if (!error)
            printf("Pass\n");

        jtest_tests++;
    }

    printf("\n");
    printf("Ran %d tests, %d assertations.\n", jtest_tests, jtest_asserts);
    return error;
}

