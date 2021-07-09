#include "list.h"

#include "unity.h"

#include "strings.h"

void setUp(void) {}

void tearDown(void) {}

void list_foreach_string_free_callback(void* s) {
    string_free((string_t*)s);
}

void test_list_equal_same_elems_should_return_true(void) {
    list_t* lhs = list_new(8);
    list_t* rhs = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    lhs = list_append(list_append(lhs, str1), str2);
    rhs = list_append(list_append(rhs, str1), str2);

    TEST_ASSERT_TRUE(list_equal(lhs, rhs));

    list_foreach(lhs, list_foreach_string_free_callback);
    list_free(lhs);
    list_free(rhs);
}

void test_list_equal_same_identity_should_return_true(void) {
    list_t* list = list_new(8);

    TEST_ASSERT_TRUE(list_equal(list, list));

    list_free(list);
}

void test_list_equal_different_size_should_return_false(void) {
    list_t* lhs = list_new(8);
    list_t* rhs = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    lhs = list_append(list_append(lhs, str1), str2);

    TEST_ASSERT_FALSE(list_equal(lhs, rhs));

    list_foreach(lhs, list_foreach_string_free_callback);
    list_free(lhs);
    list_free(rhs);
}

void test_list_equal_different_elems_should_return_false(void) {
    list_t* lhs = list_new(8);
    list_t* rhs = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    lhs = list_append(lhs, str1);
    rhs = list_append(rhs, str2);

    TEST_ASSERT_FALSE(list_equal(lhs, rhs));

    list_foreach(lhs, list_foreach_string_free_callback);
    list_foreach(rhs, list_foreach_string_free_callback);
    list_free(lhs);
    list_free(rhs);
}

void test_list_append_should_add_elements(void) {
    list_t* list = list_new(8);
    string_t* str = string("hello", 5);

    list = list_append(list, str);

    TEST_ASSERT_EQUAL(1, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_append_should_add_multiple_elements(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list_append(list, str1), str2);

    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str1, list_get(list, 0));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 1));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_copy_copy_should_equal_original(void) {
    list_t* original = list_new(8);
    list_t* copy;
    string_t* str = string("hello", 5);

    original = list_append(original, str);
    copy = list_copy(original);

    TEST_ASSERT_TRUE(list_equal(original, copy));

    list_foreach(original, list_foreach_string_free_callback);
    list_free(original);
    list_free(copy);
}

void test_list_copy_copy_should_not_modify_original(void) {
    list_t* original = list_new(8);
    list_t* copy;
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    original = list_append(original, str1);
    copy = list_append(list_copy(original), str2);

    TEST_ASSERT_FALSE(list_equal(original, copy));
    TEST_ASSERT_EQUAL(1, list_size(original));
    TEST_ASSERT_EQUAL(2, list_size(copy));

    list_foreach(original, list_foreach_string_free_callback);
    string_free(str2);
    list_free(original);
    list_free(copy);
}

void test_list_clear_should_clear_list_buffer(void) {
    list_t* list = list_new(8);
    string_t* str = string("hello", 5);

    list = list_clear(list_append(list, str));
    TEST_ASSERT_EQUAL(0, list_size(list));
    TEST_ASSERT_EQUAL_PTR(NULL, list_get(list, 0));

    string_free(str);
    list_free(list);
}

void test_list_extend_should_append_elements(void) {
    list_t* list1 = list_new(8);
    list_t* list2 = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);
    string_t* str3 = string("fizz", 4);

    list1 = list_append(list_append(list1, str1), str2);
    list2 = list_append(list2, str3);
    list1 = list_extend(list1, list2);

    TEST_ASSERT_EQUAL(3, list_size(list1));
    TEST_ASSERT_EQUAL(list_get(list2, 0), list_get(list1, 2));

    string_free(str1);
    string_free(str2);
    string_free(str3);
    list_free(list1);
    list_free(list2);
}

void test_list_extend_should_append_multiple_elements(void) {
    list_t* list1 = list_new(8);
    list_t* list2 = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);
    string_t* str3 = string("fizz", 4);
    string_t* str4 = string("buzz", 4);

    list1 = list_append(list_append(list1, str1), str2);
    list2 = list_append(list_append(list2, str3), str4);
    list1 = list_extend(list1, list2);

    TEST_ASSERT_EQUAL(4, list_size(list1));
    TEST_ASSERT_EQUAL(list_get(list2, 0), list_get(list1, 2));
    TEST_ASSERT_EQUAL(list_get(list2, 1), list_get(list1, 3));

    string_free(str1);
    string_free(str2);
    string_free(str3);
    string_free(str4);
    list_free(list1);
    list_free(list2);

}

void test_list_insert_should_add_element_at_position(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);
    string_t* str3 = string("fizz", 4);

    list = list_append(list_append(list, str1), str2);
    list = list_insert(list, 1, str3);

    TEST_ASSERT_EQUAL(3, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 2));
    TEST_ASSERT_EQUAL_PTR(str3, list_get(list, 1));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_insert_should_add_element_to_beginning(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list, str1);
    list = list_insert(list, 0, str2);

    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 0));
    TEST_ASSERT_EQUAL_PTR(str1, list_get(list, 1));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_insert_should_add_element_to_end(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list, str1);
    list = list_insert(list, 1, str2);

    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(str1, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_prepend_should_add_element_to_beginning(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);
    
    list = list_append(list, str1);
    list = list_prepend(list, str2);

    TEST_ASSERT_EQUAL(2, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str1, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_prepend_should_add_multiple_elements_to_beginning(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);
    string_t* str3 = string("fizz", 4);
    
    list = list_append(list, str1);
    list = list_prepend(list_prepend(list, str2), str3);

    TEST_ASSERT_EQUAL(3, list_size(list));
    TEST_ASSERT_EQUAL_PTR(str1, list_get(list, 2));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(str3, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_remove_should_remove_present_element(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list_append(list, str1), str2);
    list = list_remove(list, str1);

    TEST_ASSERT_EQUAL(1, list_size(list));
    TEST_ASSERT_EQUAL_PTR(NULL, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
    string_free(str1);
}

void test_list_remove_should_do_nothing_if_element_missing(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list, str1);
    list_remove(list, str2);

    TEST_ASSERT_EQUAL(1, list_size(list));
    TEST_ASSERT_EQUAL_PTR(NULL, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(str1, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
    string_free(str2);
}

void test_list_find_should_return_index_of_found_element(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list_append(list, str1), str2);

    TEST_ASSERT_EQUAL(1, list_find(list, str2));
    TEST_ASSERT_EQUAL_PTR(str2, list_get(list, list_find(list, str2)));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_find_should_return_negative_int_if_element_missing(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list, str1);

    TEST_ASSERT_EQUAL(-1, list_find(list, str2));
    TEST_ASSERT_EQUAL_PTR(NULL, list_get(list, list_find(list, str2)));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
    string_free(str2);
}

void test_list_size_should_reflect_elements(void) {
    list_t* list = list_new(8);
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);

    list = list_append(list, str1);
    TEST_ASSERT_EQUAL(1, list_size(list));

    list = list_append(list, str2);
    TEST_ASSERT_EQUAL(2, list_size(list));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_get_should_return_element_at_index(void) {
    list_t* list = list_new(8);
    string_t* str = string("hello", 5);

    list = list_append(list, str);
    TEST_ASSERT_EQUAL_PTR(str, list_get(list, 0));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
}

void test_list_get_should_return_null_if_out_of_bounds(void) {
    list_t* list = list_new(8);

    TEST_ASSERT_EQUAL_PTR(NULL, list_get(list, 0));

    list_free(list);
}

void test_list_pop_should_return_element_at_index(void) {
    list_t* list = list_new(8);
    string_t* str = string("hello", 5);

    list = list_append(list, str);

    TEST_ASSERT_EQUAL_PTR(str, list_pop(list, 0));
    TEST_ASSERT_EQUAL(0, list_size(list));

    list_free(list);
    string_free(str);
}

void test_list_pop_should_return_null_if_out_of_bounds(void) {
    list_t* list = list_new(8);

    TEST_ASSERT_EQUAL_PTR(NULL, list_pop(list, 0));

    list_free(list);

}

void test_list_slice_should_return_null_if_out_of_bounds(void) {
    list_t* list = list_new(8);

    TEST_ASSERT_EQUAL_PTR(NULL, list_slice(list, 1, 3));

    list_free(list);
}

void test_list_slice_should_return_null_if_negative_range(void) {
    list_t* list = list_new(8);

    TEST_ASSERT_EQUAL_PTR(NULL, list_slice(list, -1, -2));

    list_free(list);
}

void test_list_slice_should_return_null_if_start_after_end(void) {
    list_t* list = list_new(8);

    TEST_ASSERT_EQUAL_PTR(NULL, list_slice(list, 5, 1));

    list_free(list);
}

void test_list_slice_should_return_slice_of_elements(void) {
    list_t* list = list_new(8);
    list_t* slice;
    string_t* str1 = string("hello", 5);
    string_t* str2 = string("world", 5);
    string_t* str3 = string("fizz", 4);

    list = list_append(list_append(list_append(list, str1), str2), str3);
    slice = list_slice(list, 1, 3);

    TEST_ASSERT_EQUAL(2, list_size(slice));
    TEST_ASSERT_EQUAL_PTR(list_get(list, 1), list_get(slice, 0));
    TEST_ASSERT_EQUAL_PTR(list_get(list, 2), list_get(slice, 1));

    list_foreach(list, list_foreach_string_free_callback);
    list_free(list);
    list_free(slice);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_list_append_should_add_elements);
    RUN_TEST(test_list_append_should_add_multiple_elements);
    RUN_TEST(test_list_clear_should_clear_list_buffer);
    RUN_TEST(test_list_copy_copy_should_equal_original);
    RUN_TEST(test_list_copy_copy_should_not_modify_original);
    RUN_TEST(test_list_equal_different_elems_should_return_false);
    RUN_TEST(test_list_equal_different_size_should_return_false);
    RUN_TEST(test_list_equal_same_elems_should_return_true);
    RUN_TEST(test_list_equal_same_identity_should_return_true);
    RUN_TEST(test_list_extend_should_append_elements);
    RUN_TEST(test_list_extend_should_append_multiple_elements);
    RUN_TEST(test_list_find_should_return_index_of_found_element);
    RUN_TEST(test_list_find_should_return_negative_int_if_element_missing);
    RUN_TEST(test_list_get_should_return_element_at_index);
    RUN_TEST(test_list_get_should_return_null_if_out_of_bounds);
    RUN_TEST(test_list_insert_should_add_element_at_position);
    RUN_TEST(test_list_insert_should_add_element_to_beginning);
    RUN_TEST(test_list_insert_should_add_element_to_end);
    RUN_TEST(test_list_pop_should_return_element_at_index);
    RUN_TEST(test_list_pop_should_return_null_if_out_of_bounds);
    RUN_TEST(test_list_prepend_should_add_element_to_beginning);
    RUN_TEST(test_list_prepend_should_add_multiple_elements_to_beginning);
    RUN_TEST(test_list_remove_should_do_nothing_if_element_missing);
    RUN_TEST(test_list_remove_should_remove_present_element);
    RUN_TEST(test_list_size_should_reflect_elements);
    RUN_TEST(test_list_slice_should_return_null_if_negative_range);
    RUN_TEST(test_list_slice_should_return_null_if_out_of_bounds);
    RUN_TEST(test_list_slice_should_return_null_if_start_after_end);
    RUN_TEST(test_list_slice_should_return_slice_of_elements);

    return UNITY_END();
}
