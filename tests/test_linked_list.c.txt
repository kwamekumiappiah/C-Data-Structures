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

static void test_create_and_add(void) {
    printf("\n--- Running: Create & Add Tests ---\n");
    linkedList *list = create_linked_list();
    TEST_ASSERT(list != NULL, "List container creation");
    TEST_ASSERT(get_list_length(list) == 0, "Initial length is 0");

    int val = 42;
    add_node(list, TYPE_INT, &val);
    TEST_ASSERT(get_list_length(list) == 1, "Length increments after adding node");

    free_linked_list(list);
}

static void test_delete_by_value_edge_cases(void) {
    printf("\n--- Running: Delete by Value & Type Safety Tests ---\n");
    linkedList *list = create_linked_list();

    int head_val = 100;
    int mid_val = 200;
    char char_val = 'A'; // ASCII 65
    int int_val = 65;

    add_node(list, TYPE_INT, &head_val);
    add_node(list, TYPE_INT, &mid_val);
    add_node(list, TYPE_INT, &int_val);

    // 🛡️ Edge Case 1: Type-Mismatch (Try deleting 'A' when only integer 65 exists)
    int res = delete_node_value(list, TYPE_CHAR, &char_val);
    TEST_ASSERT(res == 1, "Refuses to delete integer 65 when searching for char 'A'");
    TEST_ASSERT(get_list_length(list) == 3, "List length remains unchanged on type mismatch");

    // 👑 Edge Case 2: Head Removal
    res = delete_node_value(list, TYPE_INT, &head_val);
    TEST_ASSERT(res == 0, "Successfully deletes head node");
    TEST_ASSERT(get_list_length(list) == 2, "Length updates after head deletion");

    // 🔍 Edge Case 3: Deleting Non-Existent Value
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

    // 🚨 Out of bounds index access
    ListElement elem = search_by_index(list, 5);
    TEST_ASSERT(elem.type == TYPE_INVALID, "Search out of bounds returns TYPE_INVALID");

    // 🚨 Out of bounds index deletion
    int res = delete_node(list, 10);
    TEST_ASSERT(res == 1, "Delete out of bounds fails safely");

    free_linked_list(list);
}

int main(void) {
    printf("=========================================\n");
    printf(" 🚀 STARTING LINKED LIST AUTOMATED TESTS \n");
    printf("=========================================\n");

    test_create_and_add();
    test_delete_by_value_edge_cases();
    test_index_bounds();

    printf("\n=========================================\n");
    printf(" 🎉 TEST SUITE COMPLETE \n");
    printf("=========================================\n");
    return 0;
}