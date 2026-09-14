#include <stdio.h>
#include "linked_list.h"

int main(void) {
    linkedList *my_linked_list = create_linked_list();
    int number = 10;
    add_node(my_linked_list, TYPE_INT, &number);
    return 0;

}