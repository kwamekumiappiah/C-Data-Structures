#include <stdio.h>
#include "linked_list.h"

int main(void) {
    linkedList *my_linked_list = create_linked_list();
    int number = 10;
    int number2 = 65;
    long long xp = 435657890;
    char letter = 'G';
    char letter2 = 'F';
    char mychar = 'A';


    add_node(my_linked_list, TYPE_INT, &number);
    add_node(my_linked_list, TYPE_LONG_LONG, &xp);
    add_node(my_linked_list, TYPE_INT, &number2);
    add_node(my_linked_list, TYPE_CHAR, &letter);

    print_linked_list(my_linked_list);
    prepend_node(my_linked_list, TYPE_CHAR, &mychar);
    print_linked_list(my_linked_list);

    reverse_list(my_linked_list);
    print_linked_list(my_linked_list);
    free_linked_list(my_linked_list);
    return 0;

}