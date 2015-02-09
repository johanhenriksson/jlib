#ifndef JTEST_H
#define JTEST_H

#include <stdlib.h>
#include "error.h"

#define jassert(desc, expr) do { jtest_asserts++; if (!(expr)) { printf("Assert error: %s at %s:%d\n", desc, __FILE__, __LINE__); return -1; } } while(0)

#define TEST_OK return 0

/* Aliases */
#define jassert_null(expr) jassert("Null value expected", expr == NULL)
#define jassert_not_null(expr) jassert("Non-null value expected", expr != NULL)
#define jassert_success(desc, expr) jassert(desc, expr == E_SUCCESS)
#define jassert_error(desc, expr, error) jassert(desc, expr == error)

/* Testcase function pointer */
typedef int (*TestCase_f)(void);

/* Functions */
int jtest_run(TestCase_f*);

/* Global variables */
extern int jtest_asserts;
extern int jtest_tests;

#endif
