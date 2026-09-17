/**
 * @file test_linked_list.c
 * @brief Automated unit test suite for the heterogeneous linked list.
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

#define TEST_ASSERT(condition, message) do { \
    if (condition) { \
        printf("🟢 [PASS] %s\n", message); \
    } else { \
        printf("🔴 [FAIL] %s (Line %d)\n", message, __LINE__); \
    } \
} while(0)

static void test_create_and_add(void) {
    printf("\n--- Running: Create, Add & Empty Tests ---\n");
    linkedList *list = create_linked_list();
    TEST_ASSERT(list != NULL, "List container creation");
    TEST_ASSERT(get_list_length(list) == 0, "Initial length is 0");
    TEST_ASSERT(is_empty(list) == 1, "New list is empty");

    int val = 42;
    add_node(list, TYPE_INT, &val);
    TEST_ASSERT(get_list_length(list) == 1, "Length increments after adding node");
    TEST_ASSERT(is_empty(list) == 0, "List is no longer empty");

    free_linked_list(list);
}

static void test_prepend_and_contains(void) {
    printf("\n--- Running: Prepend & Contains Tests ---\n");
    linkedList *list = create_linked_list();

    int val1 = 10, val2 = 20, missing_val = 99;

    prepend_node(list, TYPE_INT, &val1); // List: [10]
    prepend_node(list, TYPE_INT, &val2); // List: [20, 10]

    TEST_ASSERT(get_list_length(list) == 2, "List length is 2 after prepending twice");
    TEST_ASSERT(contains_value(list, TYPE_INT, &val2) == 0, "Finds prepended value 20");
    TEST_ASSERT(contains_value(list, TYPE_INT, &val1) == 0, "Finds original value 10");
    TEST_ASSERT(contains_value(list, TYPE_INT, &missing_val) == 1, "Returns 1 for non-existent value 99");

    free_linked_list(list);
}

int main(void) {
    printf("=========================================\n");
    printf(" 🚀 STARTING LINKED LIST AUTOMATED TESTS \n");
    printf("=========================================\n");

    test_create_and_add();
    test_prepend_and_contains();

    printf("\n=========================================\n");
    printf(" 🎉 TEST SUITE COMPLETE \n");
    printf("=========================================\n");
    return 0;
}