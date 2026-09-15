/**
 * @file linked_list.c
 * @brief Implementation of a heterogeneous, memory-safe linked list in C.
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/**
 * @struct Node
 * @brief Represents an individual element in the heterogeneous list.
 */
typedef struct Node {
    DataType type;          // Discriminator tracking the active union field
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
    struct Node *next;      // Pointer to the next node in the sequence
} Node;

/**
 * @struct linkedList
 * @brief Represents the container holding the list metadata and head pointer.
 */
typedef struct linkedList {
    size_t length;          // Total number of active nodes
    Node *head;             // Pointer to the first node
} linkedList;


/**
 * @brief Helper function to create a node.
 */
static Node *create_node(DataType type, void *data) {
    Node *ptr = malloc(sizeof(Node));
    if (!ptr) return NULL;

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
            ptr->value.void_ptr_val = data;
            break;
        default:
            free(ptr);
            return NULL;
    }
    return ptr;
}

/**
 * @brief Helper function identify and return the node just before a target node.
 */
static Node *get_node_before_target(linkedList *linked_list, size_t index) {
    Node *current_node = linked_list->head;
    size_t tracker = 0;
        
    while (tracker < index - 1) {
        Node *next_node = current_node->next;
        current_node = next_node;
        tracker++;
    }
    return current_node;
}

/**
 * @brief Insert a node at a given index.
 */

int insert_value(linkedList *linked_list, size_t index, DataType type, void *data) {
    // Validat inputs
    if (!linked_list) return 1;
    if (index > linked_list->length) return 1;

    Node *new_node = create_node(type, data);
    if (!new_node) return 1;

    // Handle Edge Case, index is 0 and linked list is not empty
    // Handle Edge Case, index is 0 and linked list is empty
    if ((index == 0) && (linked_list->length == 0)) {
        linked_list->head = new_node;
    } else if (index == 0) {                               
        Node * current_head = linked_list->head;
        linked_list->head = new_node;
        new_node->next = current_head;
    } else {
        Node *current_node = get_node_before_target(linked_list, index);
        new_node->next = current_node->next;
        current_node->next = new_node;
    }
    linked_list->length++;
    return 0;
}


/**
 * @brief Deletes a node at a specified index with bounds checking.
 */
int delete_node(linkedList *linked_list, size_t index) {
    if (!linked_list) return 0;
    if (index >= linked_list->length) return 1;

    // Handle head node removal
    if (index == 0) {
        Node *temp = linked_list->head->next;
        free(linked_list->head);
        linked_list->head = temp;
    } else {
        // Traverse to the node right before the target index
        Node *current_node = get_node_before_target(linked_list, index);
        
        // Bypass and free the target node
        Node *node_after_target = current_node->next->next;
        free(current_node->next);
        current_node->next = node_after_target;
    }
    
    linked_list->length--;
    return 0;
}

/**
 * @brief Traverses the list and prints each node's value based on its type.
 */
void print_linked_list(linkedList *linked_list) {
    if (!linked_list) return;
    
    Node *current_node = linked_list->head;
    while (current_node) {
        switch (current_node->type) {
            case TYPE_CHAR:
                printf("%c -> ", current_node->value.char_val);
                break;
            case TYPE_UNSIGNED_CHAR:
                printf("%u -> ", current_node->value.u_char_val);
                break;
            case TYPE_SHORT:
                printf("%d -> ", current_node->value.short_val);
                break;
            case TYPE_UNSIGNED_SHORT:
                printf("%u -> ", current_node->value.u_short_val);
                break;
            case TYPE_INT:
                printf("%d -> ", current_node->value.int_val);
                break;
            case TYPE_UNSIGNED_INT:
                printf("%u -> ", current_node->value.u_int_val);
                break;
            case TYPE_LONG:
                printf("%ld -> ", current_node->value.long_val);
                break;
            case TYPE_UNSIGNED_LONG:
                printf("%lu -> ", current_node->value.u_long_val);
                break;
            case TYPE_LONG_LONG:
                printf("%lld -> ", current_node->value.long_long_val);
                break;
            case TYPE_UNSIGNED_LONG_LONG:
                printf("%llu -> ", current_node->value.u_long_long_val);
                break;
            case TYPE_FLOAT:
                printf("%f -> ", current_node->value.float_val);
                break;
            case TYPE_DOUBLE:
                printf("%f -> ", current_node->value.double_val);
                break;
            case TYPE_LONG_DOUBLE:
                printf("%Lf -> ", current_node->value.long_double_val);
                break;
            case TYPE_VOID_POINTER:
                printf("%p -> ", current_node->value.void_ptr_val);
                break;
            default:
                printf("[unknown] -> ");
                break;
        }
        current_node = current_node->next;
    }
    printf("NULL\n");
}

/**
 * @brief Frees all nodes and the list container itself to prevent memory leaks.
 */
int free_linked_list(linkedList *linked_list) {
    if (linked_list == NULL) {
        return 0;
    }

    Node *current_node = linked_list->head;
    while (current_node) {    
        Node *next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    
    free(linked_list);
    return 0;
}

/**
 * @brief Allocates and appends a new node to the end of the list.
 */
int add_node(linkedList *linked_list, DataType type, void *data) {
    Node *ptr = create_node(type, data);
    if (!ptr) return 1;

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

/**
 * @brief Allocates and initializes a new linked list container.
 */
linkedList *create_linked_list(void) {
    linkedList *pointer = malloc(sizeof(linkedList));
    if (!pointer) return NULL;

    pointer->head = NULL;
    pointer->length = 0;
    return pointer;
}