/**
 * @file test_linked_list.c
 * @brief Automated unit test suite for the heterogeneous linked list.
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// 🧪 Custom Test Assertion Macro (Non-crashing)
#define TEST_ASSERT(condition, message) do { \
    if (condition) { \
        printf("🟢 [PASS] %s\n", message); \
    } else { \
        printf("🔴 [FAIL] %s (Line %d)\n", message, __LINE__); \
    } \
} while(0)

static void test_create_add_and_empty(void) {
    printf("\n--- Running: Create, Add & Empty Tests ---\n");
    linkedList *list = create_linked_list();

    // 1. Initial empty state
    TEST_ASSERT(list != NULL, "List container creation");
    TEST_ASSERT(get_list_length(list) == 0, "Initial length is 0");
    TEST_ASSERT(is_empty(list) == 1, "New list is empty");

    // 2. State after adding node
    int val = 42;
    add_node(list, TYPE_INT, &val);
    TEST_ASSERT(get_list_length(list) == 1, "Length increments after adding node");
    TEST_ASSERT(is_empty(list) == 0, "List is no longer empty");

    free_linked_list(list);
}

static void test_prepend_and_contains(void) {
    printf("\n--- Running: Prepend & Contains Tests ---\n");
    linkedList *list = create_linked_list();

    int val1 = 10;
    int val2 = 20;
    int missing_val = 99;

    // 1. Prepend nodes to front
    prepend_node(list, TYPE_INT, &val1); // List: [10]
    prepend_node(list, TYPE_INT, &val2); // List: [20, 10]

    TEST_ASSERT(get_list_length(list) == 2, "List length is 2 after prepending twice");

    // 2. Value presence checks
    TEST_ASSERT(contains_value(list, TYPE_INT, &val2) == 0, "Finds prepended value 20");
    TEST_ASSERT(contains_value(list, TYPE_INT, &val1) == 0, "Finds original value 10");
    TEST_ASSERT(contains_value(list, TYPE_INT, &missing_val) == 1, "Returns 1 for non-existent value 99");

    free_linked_list(list);
}

static void test_delete_by_value_edge_cases(void) {
    printf("\n--- Running: Delete by Value & Type Safety Tests ---\n");
    linkedList *list = create_linked_list();

    int head_val = 100;
    int mid_val = 200;
    char char_val = 'A';
    int int_val = 65;

    add_node(list, TYPE_INT, &head_val);
    add_node(list, TYPE_INT, &mid_val);
    add_node(list, TYPE_INT, &int_val);

    // 1. Type-Mismatch Protection
    int res = delete_node_value(list, TYPE_CHAR, &char_val);
    TEST_ASSERT(res == 1, "Refuses to delete integer 65 when searching for char 'A'");
    TEST_ASSERT(get_list_length(list) == 3, "List length remains unchanged on type mismatch");

    // 2. Head Node Removal
    res = delete_node_value(list, TYPE_INT, &head_val);
    TEST_ASSERT(res == 0, "Successfully deletes head node");
    TEST_ASSERT(get_list_length(list) == 2, "Length updates after head deletion");

    // 3. Deleting Non-Existent Value
    int ghost_val = 999;
    res = delete_node_value(list, TYPE_INT, &ghost_val);
    TEST_ASSERT(res == 1, "Returns failure when value is not in list");

    free_linked_list(list);
}

static void test_index_bounds(void) {
    printf("\n--- Running: Index Operations & Bounds Checking Tests ---\n");
    linkedList *list = create_linked_list();

    int val = 10;
    add_node(list, TYPE_INT, &val);

    // 1. Out of bounds search
    ListElement elem = search_by_index(list, 5);
    TEST_ASSERT(elem.type == TYPE_INVALID, "Search out of bounds returns TYPE_INVALID");

    // 2. Out of bounds deletion
    int res = delete_node(list, 10);
    TEST_ASSERT(res == 1, "Delete out of bounds fails safely");

    free_linked_list(list);
}

int main(void) {
    printf("=========================================\n");
    printf(" 🚀 STARTING LINKED LIST AUTOMATED TESTS \n");
    printf("=========================================\n");

    test_create_add_and_empty();
    test_prepend_and_contains();
    test_delete_by_value_edge_cases();
    test_index_bounds();

    printf("\n=========================================\n");
    printf(" 🎉 TEST SUITE COMPLETE \n");
    printf("=========================================\n");
    return 0;
}