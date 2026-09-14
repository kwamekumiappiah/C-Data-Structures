#include <stdio.h>
#include "linked_list.h"

int main(void) {
    linkedList *my_linked_list = create_linked_list();
    int number = 10;
    long long xp = 435657890;
    add_node(my_linked_list, TYPE_INT, &number);
    add_node(my_linked_list, TYPE_LONG_LONG, &xp);
    free_linked_list(my_linked_list);
    return 0;

}