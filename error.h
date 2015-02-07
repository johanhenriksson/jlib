#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>

/* THROW macros for common error handling */
#define THROW(r) if(r != E_SUCCESS) return r
#define THROW_NULL(a) if (a == NULL) return E_NULL_PTR
#define THROW_ALLOC(a) if (a == NULL) return E_ALLOC_FAIL
#define THROW_BOUNDS(v,a,b) if (v < a || v >= b) return E_BOUNDS

/* CATCH macro aborts execution on failure and prints an error message */
#define CATCH(e) if (e != E_SUCCESS) { error_print(e); exit(e); }

typedef enum error_t error_t;

enum error_t {
    E_SUCCESS = 0,
    E_NULL_PTR,
    E_ALLOC_FAIL,
    E_NOT_FOUND,
    E_BOUNDS,

    /* Count element - not an actual error code */
    ERROR_COUNT
};

void error_print(error_t code);

#endif
