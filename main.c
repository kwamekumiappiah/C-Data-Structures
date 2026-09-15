#include <stdio.h>
#include "linked_list.h"

int main(void) {
    linkedList *my_linked_list = create_linked_list();
    int number = 10;
    long long xp = 435657890;
    char letter = 'G';
    add_node(my_linked_list, TYPE_INT, &number);
    add_node(my_linked_list, TYPE_LONG_LONG, &xp);
    add_node(my_linked_list, TYPE_CHAR, &letter);  
    print_linked_list(my_linked_list);
    if (insert_value(my_linked_list, 4, TYPE_CHAR, &letter) != 0) printf("Error \n");
    print_linked_list(my_linked_list);
    free_linked_list(my_linked_list);
    return 0;

}