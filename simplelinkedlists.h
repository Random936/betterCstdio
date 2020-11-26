#pragma once
#include <stdio.h>
#include <stdlib.h>

/*
--------------------------------------------------
    Easy Linked Lists
--------------------------------------------------
*/

#define declareLinkedList(type, list_s, list, list_node_s, list_node) \
typedef struct list_node_s { \
    type value; \
    struct list_node_s *next; \
} list_node; \
 \
typedef struct list_s { \
    void (*createNode) (struct list_s *, type); \
    void (*print) (struct list_s *, char *); \
    int valuesize; \
    struct list_node_s *head; \
} list; \
 \
void list_createNode(list *self, type data) { \
 \
    self->valuesize++; \
    list_node *node = malloc(sizeof(list_node)); \
    node->value = data; \
 \
    if (self->head == NULL) { \
        node->next = NULL; \
        self->head = node; \
    } else { \
        node->next = self->head; \
        self->head = node; \
    } \
} \
 \
void list_print(list *self, char *formatter) { \
    list_node *temp = self->head; \
    while (temp != NULL) { \
        printf(formatter, temp->value); \
        temp = temp->next; \
    } \
} \
 \
list initList() { \
 \
    list list_default = { \
        &list_createNode, \
        &list_print, \
        0 \
    }; \
    return list_default; \
}
