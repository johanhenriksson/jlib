#include <stdlib.h>
#include <string.h>

#include "map_node.h"
#include "map.h"

error_t map_node_alloc(map_node_t** ptr, const char* key)
{
    THROW_NULL(ptr);
    *ptr = NULL;

    map_node_t* map_node = (map_node_t*)malloc(sizeof(map_node_t));
    THROW_ALLOC(map_node);

    char* key_copy = (char*)malloc(strlen(key) + 1);
    if (key_copy == NULL) {
        free(map_node);
        return E_ALLOC_FAIL;
    }

    strcpy(key_copy, key);

    map_node->hash  = map_hash(key);
    map_node->key   = key_copy;
    map_node->value = NULL;

    *ptr = map_node;
    return E_SUCCESS;
}

error_t map_node_free(map_node_t** ptr) 
{
    THROW_NULL(ptr);

    map_node_t* map_node = *ptr;
    THROW_ALLOC(map_node);
    
    free(map_node->key);
    free(map_node);
    *ptr = NULL;

    return E_SUCCESS;
}
