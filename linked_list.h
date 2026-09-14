#ifndef linked_list_h
#define linked_list_h

// Make DataType visible to both the implimentaton file and the client file
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


// Create and Destroy Linked List
typedef struct linkedList linkedList;
linkedList *create_linked_list(void);

int add_node(linkedList *linked_list, DataType type, void *data);

#endif