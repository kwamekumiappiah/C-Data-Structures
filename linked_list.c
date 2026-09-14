#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct Node {
    DataType type; // Discriminator: tracks which union field is active
    union {
        char char_val;
        unsigned char u_char_val;
        short short_val;
        unsigned short u_short_val;
        int int_val;
        unsigned int u_int_val;
        long long_val;
        unsigned long u_long_val;
        long long long_long_val;
        unsigned long long u_long_long_val;
        float float_val;
        double double_val;
        long double long_double_val;
        void *void_ptr_val;
    } value;
    struct Node* next;
} Node;


typedef struct linkedList {
    size_t length;
    Node *head;
} linkedList;

int add_node(linkedList *linked_list, DataType type, void *data) {
    Node *ptr = malloc(sizeof(Node));
    if (!ptr) return -1;
    switch (type) {
        case TYPE_CHAR:
            ptr->type = TYPE_CHAR;
            ptr->value.char_val = *(char *)data;
            break;
        case TYPE_UNSIGNED_CHAR:
            ptr->type = TYPE_UNSIGNED_CHAR;
            ptr->value.u_char_val = *(unsigned char *)data;
            break;
        case TYPE_SHORT:
            ptr->type = TYPE_SHORT;
            ptr->value.short_val = *(short *)data;
            break;
        case TYPE_UNSIGNED_SHORT:
            ptr->type = TYPE_UNSIGNED_SHORT;
            ptr->value.u_short_val = *(unsigned short *)data;
            break;
        case TYPE_INT:
            ptr->type = TYPE_INT;
            ptr->value.int_val = *(int *)data;
            break;
        case TYPE_UNSIGNED_INT:
            ptr->type = TYPE_UNSIGNED_INT;
            ptr->value.u_int_val = *(unsigned int *)data;
            break;
        case TYPE_LONG:
            ptr->type = TYPE_LONG;
            ptr->value.long_val = *(long *)data;
            break;
        case TYPE_UNSIGNED_LONG:
            ptr->type = TYPE_UNSIGNED_LONG;
            ptr->value.u_long_val = *(unsigned long *)data;
            break;
        case TYPE_LONG_LONG:
            ptr->type = TYPE_LONG_LONG;
            ptr->value.long_long_val = *(long long *)data;
            break;
        case TYPE_UNSIGNED_LONG_LONG:
            ptr->type = TYPE_UNSIGNED_LONG_LONG;
            ptr->value.u_long_long_val = *(unsigned long long *)data;
            break;
        case TYPE_FLOAT:
            ptr->type = TYPE_FLOAT;
            ptr->value.float_val = *(float *)data;
            break;
        case TYPE_DOUBLE:
            ptr->type = TYPE_DOUBLE;
            ptr->value.double_val = *(double *)data;
            break;
        case TYPE_LONG_DOUBLE:
            ptr->type = TYPE_LONG_DOUBLE;
            ptr->value.long_double_val = *(long double *)data;
            break;
        case TYPE_VOID_POINTER:
            ptr->type = TYPE_VOID_POINTER;
            ptr->value.void_ptr_val = data; // Assumes 'data' is the pointer value itself
            break;
        default:
            free(ptr);
            return -1; // Invalid type handler
    }
    ptr->next = NULL;
    if (linked_list->head == NULL) {
        linked_list->head = ptr;
    } else {
        Node *current_ptr = linked_list->head;
        while (current_ptr->next) {
            current_ptr = current_ptr->next;
        }
        current_ptr->next = ptr;
    }
    linked_list->length += 1;
    return 0;
}

linkedList *create_linked_list(void) {
    // Create a linked list
    linkedList *pointer = malloc(sizeof(linkedList));
    if (!pointer) return NULL;

    pointer->head = NULL;
    pointer->length = 0;
    return pointer;
}