#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "map.h"
#include "error.h"

int main(int argc, char* argv[]) 
{
    error_t r;

    /* linked list */
    list_t* list;
    list_alloc(&list);

    list_append(list, "hello");
    list_append(list, "there");

    list_foreach(node, list) {
        printf("%s\n", (char*)node->node);
    }

    list_free(&list);

    /* map */
    map_t* map;
    if (map_alloc(&map) != E_SUCCESS)
        exit(-1);

    int value;

    map_set(map, "hello", (void*)5);
    map_set(map, "there", (void*)5);
    r = map_get_int(map, "hello", &value);
    if (r != E_SUCCESS)
        printf("get error: %d\n", r);
    
    printf("stored value at 'hello': %d\n", value);

    map_set(map, "hello", (void*)7);
    r = map_get_int(map, "hello", &value);
    if (r != E_SUCCESS)
        printf("get error: %d\n", r);
    printf("stored value at 'hello': %d\n", value);

    r = map_get_int(map, "not_there", &value);
    CATCH(r);

    map_free(&map);

    return E_SUCCESS;
}
