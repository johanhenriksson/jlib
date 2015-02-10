#include <stdlib.h>
#include <stdio.h>

#include "../jtest.h"
#include "../error.h"
#include "../list.h"

int test_list_alloc()
{
    error_t e;
    list_t* list;

    e = list_alloc(&list);
    jassert_success("list_alloc() failed", e);
    jassert_null(list->node);
    jassert_null(list->next);
    jassert_null(list->prev);

    free(list);
    return E_SUCCESS;
}

int test_list_free()
{
    error_t e;
    list_t* list;

    e = list_alloc(&list);
    jassert_success("list_alloc() failed", e);

    e = list_free_node(&list);
    jassert_success("list_free() failed", e);
    jassert_null(list);

    return E_SUCCESS;
}

int test_list_append()
{
    error_t e;
    list_t* head;

    e = list_alloc(&head);
    jassert_success("list_alloc() failed", e);

    e = list_append(head, (void*)1);
    jassert_success("list_append() failed", e);

    jassert_null(head->next);
    jassert_null(head->prev);
    jassert("Expected head value to be 1", (int)head->node == 1);

    e = list_append(head, (void*)2);
    jassert_success("list_append() failed", e);

    jassert_not_null(head->next);
    list_t* node = head->next;

    jassert("Invalid prev reference", node->prev == head);
    jassert_null(node->next);
    jassert("Expected node value to be 2", (int)node->node == 2);

    list_free(&head);

    return E_SUCCESS;
}

int test_list_length()
{
    error_t e;
    list_t* head;
    list_t* node;
    int count1, count2;

    e = list_alloc(&head);
    jassert_success("list_alloc() failed", e);

    e = list_length(head, &count1);
    jassert_success("list_length() failed", e);
    jassert("Expected length to be 0", count1 == 0);

    /* Append first element */
    e = list_append(head, (void*)1);
    jassert_success("list_append() failed", e);

    e = list_length(head, &count1);
    jassert_success("list_length() failed", e);
    jassert("Expected length to be 1", count1 == 1);

    /* Append second element */
    e = list_append(head, (void*)2);
    jassert_success("list_append() failed", e);

    e = list_length(head, &count1);
    jassert("Expected length to be 2", count1 == 2);

    node = head->next;

    /* Count nodes from the second element */
    e = list_length(node, &count2);
    jassert_success("list_length() failed", e);
    jassert("Expected count to be 2", count2 == 2);

    return E_SUCCESS;
}
