/**
 * @file test_linked_list.c
 * @brief Complete unit test suite for the heterogeneous linked list library.
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

// 🧪 Custom Test Assertion Macro
#define TEST_ASSERT(condition, message) do { \
    if (condition) { \
        printf("🟢 [PASS] %s\n", message); \
    } else { \
        printf("🔴 [FAIL] %s (Line %d)\n", message, __LINE__); \
    } \
} while(0)

static void test_lifecycle_and_utility(void) {
    printf("\n--- 1. Testing Creation, Empty State & Length ---\n");
    linkedList *list = create_linked_list();
    
    TEST_ASSERT(list != NULL, "List created successfully");
    TEST_ASSERT(is_empty(list) == 1, "New list is empty");
    TEST_ASSERT(get_list_length(list) == 0, "New list length is 0");

    int val = 10;
    add_node(list, TYPE_INT, &val);

    TEST_ASSERT(is_empty(list) == 0, "List is not empty after adding node");
    TEST_ASSERT(get_list_length(list) == 1, "List length updated to 1");

    free_linked_list(list);
}

static void test_insertion_modes(void) {
    printf("\n--- 2. Testing Add, Prepend & Insert Value ---\n");
    linkedList *list = create_linked_list();

    int v1 = 10, v2 = 20, v3 = 30;

    add_node(list, TYPE_INT, &v1);        // List: [10]
    prepend_node(list, TYPE_INT, &v2);    // List: [20, 10]
    insert_value(list, 1, TYPE_INT, &v3); // List: [20, 30, 10]

    TEST_ASSERT(get_list_length(list) == 3, "Length is 3 after insertions");

    ListElement e0 = search_by_index(list, 0);
    ListElement e1 = search_by_index(list, 1);
    ListElement e2 = search_by_index(list, 2);

    TEST_ASSERT(*(int *)e0.data == 20, "Index 0 holds prepended value 20");
    TEST_ASSERT(*(int *)e1.data == 30, "Index 1 holds inserted value 30");
    TEST_ASSERT(*(int *)e2.data == 10, "Index 2 holds original value 10");

    free_linked_list(list);
}

static void test_search_functions(void) {
    printf("\n--- 3. Testing Search by Index & Value ---\n");
    linkedList *list = create_linked_list();

    int int_val = 42;
    char char_val = 'Z';
    add_node(list, TYPE_INT, &int_val);
    add_node(list, TYPE_CHAR, &char_val);

    // Search by index
    ListElement e_found = search_by_index(list, 1);
    ListElement e_invalid = search_by_index(list, 99);

    TEST_ASSERT(e_found.type == TYPE_CHAR && *(char *)e_found.data == 'Z', "Search by index 1 finds char 'Z'");
    TEST_ASSERT(e_invalid.type == TYPE_INVALID, "Out of bounds search returns TYPE_INVALID");

    // Search by value
    ListElement s_found = search_by_value(list, TYPE_INT, &int_val);
    int missing = 999;
    ListElement s_missing = search_by_value(list, TYPE_INT, &missing);

    TEST_ASSERT(s_found.type == TYPE_INT && *(int *)s_found.data == 42, "Search by value finds integer 42");
    TEST_ASSERT(s_missing.type == TYPE_INVALID, "Search for non-existent value returns TYPE_INVALID");

    free_linked_list(list);
}

static void test_deletion_modes(void) {
    printf("\n--- 4. Testing Delete by Index & Value ---\n");
    linkedList *list = create_linked_list();

    int v1 = 100, v2 = 200, v3 = 300;
    add_node(list, TYPE_INT, &v1);
    add_node(list, TYPE_INT, &v2);
    add_node(list, TYPE_INT, &v3); // List: [100, 200, 300]

    // Delete by value
    int del_res = delete_node_value(list, TYPE_INT, &v1);
    TEST_ASSERT(del_res == 0, "Delete head node by value succeeds");
    TEST_ASSERT(get_list_length(list) == 2, "Length is 2 after deletion");

    // Delete by index
    del_res = delete_node(list, 1); // Deletes 300
    TEST_ASSERT(del_res == 0, "Delete node by index succeeds");
    TEST_ASSERT(get_list_length(list) == 1, "Length is 1 after second deletion");

    free_linked_list(list);
}

static void test_cloning_and_display(void) {
    printf("\n--- 5. Testing Deep Clone & List Print ---\n");
    linkedList *original = create_linked_list();

    int v1 = 5, v2 = 15;
    add_node(original, TYPE_INT, &v1);
    add_node(original, TYPE_INT, &v2);

    printf("Visual Check - Original List:\n");
    print_linked_list(original);

    linkedList *clone = clone_list(original);
    TEST_ASSERT(clone != NULL, "Cloned list creation");
    TEST_ASSERT(clone != original, "Clone is at a distinct memory address");
    TEST_ASSERT(get_list_length(clone) == get_list_length(original), "Clone has matching length");

    // Verify independent state
    delete_node(clone, 0);
    TEST_ASSERT(get_list_length(clone) == 1, "Deleting from clone reduces clone length");
    TEST_ASSERT(get_list_length(original) == 2, "Original list length remains unaffected");

    free_linked_list(original);
    free_linked_list(clone);
}

static void test_reverse_list(void) {
    printf("\n--- 6. Testing List Reversal ---\n");
    linkedList *list = create_linked_list();

    int v1 = 10, v2 = 20, v3 = 30;
    add_node(list, TYPE_INT, &v1);
    add_node(list, TYPE_INT, &v2);
    add_node(list, TYPE_INT, &v3); // List: [10, 20, 30]

    int status = reverse_list(list);
    TEST_ASSERT(status == 0, "Reverse list function executed successfully");

    ListElement first = search_by_index(list, 0);
    ListElement last = search_by_index(list, 2);

    TEST_ASSERT(*(int *)first.data == 30, "Index 0 now holds 30 (new head)");
    TEST_ASSERT(*(int *)last.data == 10, "Index 2 now holds 10 (new tail)");

    free_linked_list(list);
}

int main(void) {
    printf("=========================================\n");
    printf(" 🚀 STARTING LINKED LIST FULL TEST SUITE \n");
    printf("=========================================\n");

    test_lifecycle_and_utility();
    test_insertion_modes();
    test_search_functions();
    test_deletion_modes();
    test_cloning_and_display();
    test_reverse_list();

    printf("\n=========================================\n");
    printf(" 🎉 ALL TESTS COMPLETED \n");
    printf("=========================================\n");
    return 0;
}