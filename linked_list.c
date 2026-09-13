#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef enum {
    TYPE_CHAR,
    TYPE_UNSIGNED_CHAR,
    TYPE_SHORT,
    TYPE_UNSIGNED_SHORT,
    TYPE_INT,
    TYPE_UNSIGNED_INT,
    TYPE_LONG,
    TYPE_UNSIGNED_LONG,
    TYPE_LONG_LONG,
    TYPE_UNSIGNED_LONG_LONG,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_VOID_POINTER
} DataType;

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

linkedList *create_linked_list(void) {
    linkedList *pointer = malloc(sizeof(linkedList));
    if (!pointer) return NULL;
    
    pointer->head = NULL;
    pointer->length = 0;
    return pointer;
}