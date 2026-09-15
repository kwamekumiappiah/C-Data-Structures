#include <stdio.h>
#include "linked_list.h"

int main(void) {
    linkedList *my_linked_list = create_linked_list();
    int number = 10;
    long long xp = 435657890;
    char letter = 'G';
    void *num_ptr = &number;
    printf("%p\n", num_ptr);
    printf("%d\n", *(int *)num_ptr);


    add_node(my_linked_list, TYPE_INT, &number);
    add_node(my_linked_list, TYPE_LONG_LONG, &xp);
    add_node(my_linked_list, TYPE_CHAR, &letter);
    add_node(my_linked_list, TYPE_VOID_POINTER, num_ptr);  
    printf("%p\n", num_ptr);
    print_linked_list(my_linked_list);

    printf("%p\n", num_ptr);
    ListElement return_data = search_by_index(my_linked_list, 3);
    printf("\nPointer of data: %p\nData type: %d\n\n", return_data.data, return_data.type);
    printf("%p\n", (void **)return_data.data);
    int num = *(int *)((void **)return_data.data);
    printf("%d", num);
    free_linked_list(my_linked_list);
    return 0;

}