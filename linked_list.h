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

// Allow values to be returned instead of the list buy usinf a void pointer and a type tracker
typedef struct {
    DataType type;
    void *data;
} ListElement;

// Create and Destroy Linked List
typedef struct linkedList linkedList;
linkedList *create_linked_list(void);
int free_linked_list(linkedList *linked_list);

// Add and Remove Nodes
int add_node(linkedList *linked_list, DataType type, void *data);
int insert_value(linkedList *linked_list, size_t index, DataType type, void *data);
int delete_node(linkedList * linked_list, size_t index);

// Display Information
void print_linked_list(linkedList *linked_list);

// Search for information
ListElement search_by_index(linkedList *linked_list, size_t index);


#endif