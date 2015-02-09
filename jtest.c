#include <stdlib.h>
#include <stdio.h>

#include "jtest.h"

int jtest_run(TestCase_f* tests) 
{
    int error;
    int ran = 0;

    for(int t = 0; ; t++)
    {
        TestCase_f test_func = tests[t];
        if (test_func == NULL)
            break;

        error = test_func(); 
        if (!error)
            printf("Pass\n");

        ran++;
    }

    printf("\n");
    printf("Ran %d tests.\n", ran);
    return error;
}

