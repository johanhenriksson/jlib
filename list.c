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
    list->node = NULL;
    *ptr = list;

    return E_SUCCESS;
}

error_t list_free(list_t** ptr)
{
    THROW_NULL(ptr);

    list_t* current = *ptr;
    THROW_NULL(current);

    while(current->next != NULL) 
    {
        list_t* temp = current;
        current = current->next;

        /* free node */
        free(temp);
    }

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
    tail->next = node;
    
    return E_SUCCESS;
}

error_t list_tail(list_t* head, list_t** tail) 
{
    THROW_NULL(head);

    list_t* current = head;
    while(current->next != NULL)
        current = current->next;

    *tail = current;
    return E_SUCCESS;
}

error_t list_count(list_t* head, int* count) 
{
    THROW_NULL(head);

    *count = 0;

    if (head->node == NULL) 
        return E_SUCCESS;

    list_t* current = head;
    while(current->next != NULL) {
        current = current->next;
        (*count)++;
    }

    return E_SUCCESS;
}

error_t list_remove(list_t** head, void* element)
{
    THROW_NULL(head);
    THROW_NULL(element);

    list_t* node = *head;
    list_t* prev = NULL;

    while(node != NULL) 
    {
        if (node->node == element) {
            /* replace or empty list head */
            if (prev == NULL) {
                if (node->next != NULL)
                    *head = node->next;
                else {
                    (*head)->node = NULL;
                    /* we dont want to free the node, return here */
                    return E_SUCCESS;
                }
            }
            else 
                prev->next = node->next;

            /* free node & return success */
            free(node);
            return E_SUCCESS;
        }

        prev = node;
        node = node->next;
    }

    return E_NOT_FOUND;
}
