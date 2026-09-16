#include <stdio.h>
#include "linked_list.h"

int main(void) {
    linkedList *my_linked_list = create_linked_list();
    int number = 10;
    int number2 = 20;
    long long xp = 435657890;
    char letter = 'G';
    char letter2 = 'F';


    add_node(my_linked_list, TYPE_INT, &number);
    add_node(my_linked_list, TYPE_LONG_LONG, &xp);
    add_node(my_linked_list, TYPE_INT, &number2);
    add_node(my_linked_list, TYPE_CHAR, &letter);

    print_linked_list(my_linked_list);
    ListElement return_data = search_by_value(my_linked_list, TYPE_INT, &number2);
    // printf("%p\n", return_data.data);
    // printf("%d\n", return_data.type);
    printf("%d\n%d\n", return_data.type, *(int *)return_data.data);
    *(int *)return_data.data = 50;
    print_linked_list(my_linked_list);
    free_linked_list(my_linked_list);
    return 0;

}