#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/** Allocate a list node */
error_t list_alloc(list_t** ptr) 
{
    THROW_NULL(ptr);
    *ptr = NULL;

    list_t* list = malloc(sizeof(list_t));
    THROW_ALLOC(list);

    list->next = NULL;
    list->prev = NULL;
    list->node = NULL;
    *ptr = list;

    return E_SUCCESS;
}

error_t list_free(list_t** ptr)
{
    THROW_NULL(ptr);

    list_t* node = *ptr;
    list_t* current;
    THROW_NULL(node);

    /* Free previous nodes */
    if (node->prev != NULL) {
        current = node->prev;
        while(current != NULL) {
            list_t* temp = current;
            current = current->prev;
            list_free_node(&temp);
        }
    }

    current = node;
    while(current != NULL) { 
        list_t* temp = current;
        current = current->next;
        list_free_node(&temp);
    }

    return E_SUCCESS;
}

error_t list_free_node(list_t** ptr)
{
    THROW_NULL(ptr);
    list_t* node = *ptr;
    THROW_NULL(node);

    free(node);
    *ptr = NULL;
     
    return E_SUCCESS;
}

error_t list_append(list_t* list, void* element) 
{
    THROW_NULL(list);

    /* special case: empty list */
    if (list->node == NULL) {
        list->node = element;
        return E_SUCCESS;
    }

    /* find tail */
    list_t* tail; 
    error_t result;
    result = list_tail(list, &tail);
    THROW(result);

    /* create a node */
    list_t* node;
    result = list_alloc(&node);
    THROW(result);

    node->node = element;
    node->prev = tail;
    tail->next = node;
    
    return E_SUCCESS;
}

error_t list_tail(list_t* node, list_t** tail) 
{
    THROW_NULL(node);
    THROW_NULL(tail);
    *tail = NULL;

    list_t* current = node;
    while(current->next != NULL)
        current = current->next;

    *tail = current;
    return E_SUCCESS;
}

error_t list_head(list_t* node, list_t** head)
{
    THROW_NULL(node);
    THROW_NULL(head);
    *head = NULL;

    list_t* current = node;
    while(current->prev != NULL)
        current = current->prev;

    *head = current;
    return E_SUCCESS;
}

error_t list_count(list_t* node, int* count) 
{
    THROW_NULL(node);

    *count = 0;

    if (node->node == NULL) 
        return E_SUCCESS;

    list_t* current;
    
    /* count items after node */
    current = node;
    while(current->next != NULL) {
        current = current->next;
        (*count)++;
    }

    /* count items ahead of node */
    current = node;
    while(current->prev != NULL) {
        current = current->prev;
        (*count)++;
    }

    return E_SUCCESS;
}

error_t list_remove(list_t** node_ptr)
{
    THROW_NULL(node_ptr);

    list_t* node = *node_ptr;
    THROW_NULL(node);

    /* Special case: only node in list */
    if (node->next == NULL && node->prev == NULL) {
        node->node = NULL;
        return E_SUCCESS;
    }

    /* Case: First node */
    if (node->next != NULL && node->prev == NULL) {
        node->next->prev = NULL;
        list_free_node(node_ptr);
        return E_SUCCESS;
    }

    /* Case: Last node */
    if (node->next == NULL && node->prev != NULL) {
        node->prev->next = NULL;
        list_free_node(node_ptr);
        return E_SUCCESS;
    }

    /* Somewhere in the middle */
    node->prev->next = node->next;
    node->next->prev = node->prev;
    list_free_node(node_ptr);

    return E_SUCCESS;
}

error_t list_length(list_t* node, int* count) 
{
    THROW_NULL(node);
    THROW_NULL(count);

    *count = 0;

    list_t* current;

    /* Count previous nodes */
    if (node->prev != NULL) {
        current = node->prev;
        while(current != NULL) {
            (*count)++;
            current = current->prev;
        }
    }

    if (node->next != NULL) {
        current = node->next;
        while(current != NULL) {
            (*count)++;
            current = current->next;
        }
    }

    if (node->node != NULL)
        (*count)++;

    return E_SUCCESS;
}
