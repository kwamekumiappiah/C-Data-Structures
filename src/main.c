/**
 * @file main.c
 * @brief Minimal reproducer for the uninitialized `next` pointer bug in
 *        insert_value() / prepend_node().
 *
 * Bug: when a node is inserted at index 0 into an EMPTY list, insert_value()
 * sets linked_list->head = new_node but never sets new_node->next. Since
 * create_node() doesn't initialize `next` either, the first node in the list
 * ends up with a garbage `next` pointer. Traversing the list (print, search,
 * free, etc.) then reads/follows that garbage pointer -> undefined behavior,
 * usually a crash.
 *
 * To build and run:
 *   gcc -std=c11 -Wall -Wextra -g -fsanitize=address,undefined \
 *       -o main main.c linked_list.c
 *   ./main
 *
 * (The sanitizer flags aren't required to see the crash, but they make the
 * cause obvious instead of just segfaulting with no explanation.)
 */

#include <stdio.h>
#include "linked_list.h"

int main(void) {
    printf("Creating an empty list...\n");
    linkedList *list = create_linked_list();

    printf("Prepending a single int (42) into the empty list...\n");
    int v = 42;
    prepend_node(list, TYPE_INT, &v);   // index-0 insert into an empty list

    printf("length = %zu\n", get_list_length(list));

    printf("Printing the list (this is where it crashes)...\n");
    print_linked_list(list);   // walks head->next, which was never initialized

    printf("If you see this line, the bug is fixed.\n");

    free_linked_list(list);
    return 0;
}