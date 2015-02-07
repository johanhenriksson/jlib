#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include "error.h"

/* foreach statement */
#define list_foreach(var_name, list_node) for(list_t* var_name = list_node; var_name != NULL; var_name = var_name->next)

typedef struct list_t list_t;

/* Represents a node in a single-linked list */
struct list_t {
    void*   node;
    list_t* next;
};

error_t list_alloc(list_t**);
error_t list_free(list_t**);

error_t list_append(list_t*, void*);
error_t list_tail(list_t*, list_t**); 
error_t list_find(list_t*, void*, list_t**);
error_t list_remove(list_t**, void*);

error_t list_length(list_t*, int*);
error_t list_contains(list_t*, void*, bool*);
error_t list_empty(list_t*, bool*);

#endif
