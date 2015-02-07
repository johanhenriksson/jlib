#ifndef MAP_H
#define MAP_H

#include "array.h"
#include "list.h"
#include "error.h"
#include "map_node.h"

#define MAP_BUCKET_COUNT (10)

typedef struct map_t map_t;

struct map_t {
    int count;
    array_t* buckets;
};

error_t map_alloc(map_t**);
error_t map_free(map_t**);

error_t map_set(map_t*, const char*, void*);
error_t map_get(map_t*, const char*, void**);
error_t map_delete(map_t*, const char*);

/* aliases */
error_t map_get_int(map_t*, const char*, int*);

unsigned int map_hash(const char*);

#endif
