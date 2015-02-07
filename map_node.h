#ifndef MAP_NODE_H
#define MAP_NODE_H

#include "error.h"

typedef struct map_node_t map_node_t;

struct map_node_t {
    char* key;
    void* value;
    unsigned int hash;
};

error_t map_node_alloc(map_node_t**, const char*);
error_t map_node_free(map_node_t**);

#endif
