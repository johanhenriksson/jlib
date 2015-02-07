#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "array.h"

#include <stdio.h>

error_t map_alloc(map_t** ptr)
{
    *ptr = NULL;

    map_t* map = malloc(sizeof(map_t));
    if (map == NULL)
        return E_ALLOC_FAIL;

    error_t result = array_alloc(&map->buckets, MAP_BUCKET_COUNT);
    if (result != E_SUCCESS) {
        free(map);
        return result;
    }

    array_clear(map->buckets);

    *ptr = map;
    return E_SUCCESS;
}

error_t map_free(map_t** ptr)
{
    if (ptr == NULL)
        return E_NULL_PTR;

    map_t* map = *ptr;
    if (map == NULL)
        return E_NULL_PTR;

    list_t* bucket;
    for(int i = 0; i < map->buckets->length; i++) {
        bucket = map->buckets->ptr[i];
        if (bucket == NULL)
            continue;
        list_foreach(node, bucket) {
            if (node->node == NULL)
                break;
            map_node_t* map_node = (map_node_t*)node->node;
            map_node_free(&map_node);
        }
        list_free(&bucket);
    }

    free(map);
    *ptr = NULL;

    return E_SUCCESS;
}

error_t map_set(map_t* map, const char* key, void* value) 
{
    if (map == NULL)
        return E_NULL_PTR;

    error_t result;
    unsigned int hash = map_hash(key);
    int idx = hash % map->buckets->length;

    list_t* bucket = map->buckets->ptr[idx]; // no need for bounds checking here
    if (bucket == NULL) {
        /* bucket is empty. allocate a new list */
        result = list_alloc(&bucket);
        if (result != E_SUCCESS)
            return result;

        map->buckets->ptr[idx] = bucket;
    }

    map_node_t* map_node;

    /* look for existing node */
    list_foreach(node, bucket) {
        if (node->node == NULL)
            break;

        map_node = (map_node_t*)node->node;
        if (map_node->hash != hash)
            continue;

        if (strcmp(key, map_node->key) == 0) {
            /* we found and existing node, update it! */
            map_node->value = value;
            return E_SUCCESS;
        }
    }

    /* allocate a new node */
    result = map_node_alloc(&map_node, key);
    if (result != E_SUCCESS)
        return result;

    map_node->value = value;

    /* append node to bucket */
    list_append(bucket, map_node);

    return E_SUCCESS;
}

error_t map_get(map_t* map, const char* key, void** value)
{
    if (map == NULL)
        return E_NULL_PTR;

    error_t result;
    unsigned int hash = map_hash(key);
    int idx = hash % map->buckets->length;

    list_t* bucket = map->buckets->ptr[idx]; // no need for bounds checking here
    if (bucket == NULL) {
        *value = NULL;
        return E_NOT_FOUND;
    }

    map_node_t* map_node;
    list_foreach(node, bucket) 
    {
        if (node->node == NULL)
            break;

        map_node = (map_node_t*)node->node;
        if (map_node->hash != hash)
            continue;

        if (strcmp(key, map_node->key) == 0) {
            *value = map_node->value;
            return E_SUCCESS;
        }
    }

    return E_NOT_FOUND;
}

/* delete by key */
error_t map_delete(map_t* map, const char* key)
{
    if (map == NULL)
        return E_NULL_PTR;

    error_t result;
    unsigned int hash = map_hash(key);
    int idx = hash % map->buckets->length;

    list_t* bucket = map->buckets->ptr[idx]; // no need for bounds checking here
    if (bucket == NULL) 
        return E_NOT_FOUND;

    map_node_t* map_node;
    list_foreach(node, bucket) 
    {
        if (node->node == NULL)
            break;

        map_node = (map_node_t*)node->node;
        if (map_node->hash != hash)
            continue;

        if (strcmp(key, map_node->key) == 0) {
            /* found it! */
            map_node_free(&map_node);
            list_remove(&bucket, node);
            return E_SUCCESS;
        }
    }

    return E_NOT_FOUND;
}

error_t map_get_int(map_t* map, const char* key, int* intval)
{
    void* value;
    error_t result = map_get(map, key, &value);
    if (result != E_SUCCESS)
        return result;

    *intval = (int)value;
    return E_SUCCESS;
}

unsigned int map_hash(const char* string)
{
    int c;
    unsigned int hash = 5381;

    while ((c = *string++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
