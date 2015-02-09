#ifndef JTEST_H
#define JTEST_H

#include <stdlib.h>
#include "error.h"

#define jassert(desc, expr) do { if (!(expr)) { printf("Assert error: %s at %s:%d", desc, __FILE__, __LINE__); return -1; } } while(0)

#define TEST_OK return 0

/* Aliases */
#define jassert_not_null(expr) jassert("Is null: expr", expr != NULL)
#define jassert_success(desc, expr) jassert(desc, expr == E_SUCCESS)
#define jassert_error(desc, expr) jassert(desc, expr != E_SUCCESS)

typedef int (*TestCase_f)(void);

/* Functions */
void jtest_run(TestCase_f*);

#endif
