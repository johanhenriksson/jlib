#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "array_list.h"
#include "map.h"
#include "error.h"
#include "string.h"

int main(int argc, char* argv[]) 
{
    error_t r;

    string_t* base_str;
    r = string_const(&base_str, "hello world!");
    CATCH(r);

    array_list_t* words;
    r = string_split(base_str, &words, ' ');
    CATCH(r);

    for(int i = 0; i < words->count; i++) {
        string_t* word = (string_t*)words->values->ptr[i];
        printf("word: %s\n", word->ptr);
    }

    string_t* joined;
    string_join_with((string_t*)words->values->ptr[0], (string_t*)words->values->ptr[1], " and ", &joined);
    printf("joined: %s\n", joined->ptr);

    /* linked list */
    list_t* list;
    list_alloc(&list);

    list_append(list, "hello");
    list_append(list, "there");

    list_foreach(node, list) {
        printf("%s\n", (char*)node->node);
    }

    list_free(&list);

    /* array list */

    array_list_t* arlist;
    array_list_alloc(&arlist);

    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");
    array_list_append(arlist, "hi");

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

    map_delete(map, "hello");

    r = map_get_int(map, "hello", &value);
    CATCH(r);

    map_free(&map);

    return E_SUCCESS;
}
