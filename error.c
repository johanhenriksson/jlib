#include <stdio.h>

#include "error.h"

const char* _ERROR_MSG[ERROR_COUNT] = {
    "No Error",
    "Null pointer",
    "Allocation failed",
    "Not found",
    "Index out of bounds",
};

void error_print(error_t code)
{
    if (code >= ERROR_COUNT) {
        error_print(E_BOUNDS);
        return;
    }

    printf("Error: %s\n", _ERROR_MSG[code]);
}
