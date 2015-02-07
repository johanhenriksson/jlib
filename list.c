#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/** Allocate a list node */
error_t list_alloc(list_t** ptr) 
{
    if (ptr == NULL)
        return E_NULL_PTR;
    *ptr = NULL;

    list_t* list = malloc(sizeof(list_t));
    if (list == NULL)
        return E_ALLOC_FAIL;

    list->next = NULL;
    list->node = NULL;

    *ptr = list;

    return E_SUCCESS;
}

error_t list_free(list_t** list)
{
    if (list == NULL)
        return E_NULL_PTR;

    list_t* current = *list;
    if (current == NULL)
        return E_NULL_PTR;

    while(current->next != NULL) 
    {
        list_t* temp = current;
        current = current->next;

        /* free node */
        free(temp);
    }

    *list = NULL;
    return E_SUCCESS;
}

error_t list_append(list_t* list, void* element) 
{
    error_t result;

    /* special case: empty list */
    if (list->node == NULL) {
        list->node = element;
        return E_SUCCESS;
    }

    /* find tail */
    list_t* tail; 
    result = list_tail(list, &tail);
    if (result != E_SUCCESS)
        return result;

    /* create a node */
    list_t* node;
    result = list_alloc(&node);
    if (result != E_SUCCESS)
        return result;

    node->node = element;
    tail->next = node;
    
    return E_SUCCESS;
}

error_t list_tail(list_t* head, list_t** tail) 
{
    if (head == NULL)
        return E_NULL_PTR;

    list_t* current = head;
    while(current->next != NULL)
        current = current->next;

    *tail = current;
    return E_SUCCESS;
}

error_t list_count(list_t* head, int* count) 
{
    if (head == NULL)
        return E_NULL_PTR;

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
    if (head == NULL || element == NULL)
        return E_NULL_PTR;

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
