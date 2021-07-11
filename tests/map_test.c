#include "unity.h"

#include "map.h"
#include "strings.h"
#include "tuple.h"

void setUp(void) {}

void tearDown(void) {}

void test_map_copy_should_return_a_new_copy(void) {
    map_t* original = map_new(2, 8);
    map_t* copy = map_copy(original, 2, 8);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_TRUE(map_equal(original, copy));
    
    map_free(original);
    map_free(copy);
}

void test_map_copy_should_create_copy_equal_to_original(void) {
    map_t* original = map_new(2, 8);
    map_t* copy;
    string_t* key; 
    tuple_t* value;

    key = string("hello", 5);
    value = tuple_new(0, 0);    
    original = map_set(original, key, value);
    copy = map_copy(original, 2, 8);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_TRUE(map_equal(original, copy));
    TEST_ASSERT_EQUAL_PTR(map_get(original, key), map_get(copy, key));
    
    map_free(original);
    map_free(copy);
    string_free(key);
    tuple_free(value);
}

void test_map_copy_should_not_modify_original(void) {
    map_t* original = map_new(2, 8);
    map_t* copy;
    string_t* key1 = string("hello", 5);
    string_t* key2 = string("world", 5);
    tuple_t* value = tuple_new(0, 0);

    original = map_set(original, key1, value);
    copy = map_copy(original, 2, 8);
    copy = map_set(copy, key2, value);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_FALSE(map_equal(original, copy));
    TEST_ASSERT_EQUAL_PTR(value, map_get(copy, key2));
    TEST_ASSERT_EQUAL_PTR(NULL, map_get(original, key2));

    map_free(original);
    map_free(copy);
    string_free(key1);
    string_free(key2);
    tuple_free(value);
}

void test_map_clear_should_remove_all_elements(void) {
    map_t* map = map_new(2, 8);
    string_t* key1 = string("hello", 5);
    string_t* key2 = string("world", 5);
    tuple_t* value = tuple_new(0, 0);

    map = map_set(map_set(map, key1, value), key2, value);
    map = map_clear(map);

    TEST_ASSERT_EQUAL_PTR(NULL, map_get(map, key1));
    TEST_ASSERT_EQUAL_PTR(NULL, map_get(map, key2));

    map_free(map);
    string_free(key1);
    string_free(key2);
    tuple_free(value);
}

void test_map_set_should_set_key_to_value(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("hello", 5);
    tuple_t* value = tuple_new(0, 0);

    map = map_set(map, key, value);

    TEST_ASSERT_EQUAL_PTR(value, map_get(map, key));

    map_free(map);
    string_free(key);
    tuple_free(value);
}

void test_map_set_should_overwrite_old_value(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("hello", 5);
    tuple_t* value1 = tuple_new(0, 0);
    tuple_t* value2 = tuple_new(string("foo", 3), string("bar", 3));

    map = map_set(map_set(map, key, value1), key, value2);

    TEST_ASSERT_EQUAL_PTR(value2, map_get(map, key));

    map_free(map);
    string_free(key);
    string_free((string_t*) value2->first);
    string_free((string_t*) value2->second);
    tuple_free(value1);
    tuple_free(value2);
}

void test_map_equal_should_return_false_if_different_keys(void) {
    map_t* map1 = map_new(2, 8);
    map_t* map2 = map_new(2, 8);
    string_t* key1 = string("hello", 5);
    string_t* key2 = string("world", 5);
    tuple_t* value = tuple_new(0, 0);

    map1 = map_set(map1, key1, value);
    map2 = map_set(map2, key2, value);

    TEST_ASSERT_FALSE(map_equal(map1, map2));

    map_free(map1);
    map_free(map2);
    string_free(key1);
    string_free(key2);
    tuple_free(value);
}

void test_map_equal_should_return_false_if_different_values(void) {
    map_t* map1 = map_new(2, 8);
    map_t* map2 = map_new(2, 8);
    string_t* key = string("hello", 5);
    tuple_t* value1 = tuple_new(0, 0);
    tuple_t* value2 = tuple_new(string("foo", 3), string("bar", 3));

    map1 = map_set(map1, key, value1);
    map2 = map_set(map2, key, value2);

    TEST_ASSERT_FALSE(map_equal(map1, map2));

    map_free(map1);
    map_free(map2);
    string_free(key);
    string_free((string_t*) value2->first);
    string_free((string_t*) value2->second);
    tuple_free(value1);
    tuple_free(value2);
}

void test_map_equal_should_return_false_if_different_pairs(void) {
    map_t* map1 = map_new(2, 8);
    map_t* map2 = map_new(2, 8);
    string_t* key1 = string("hello", 5);
    string_t* key2 = string("world", 5);
    tuple_t* value1 = tuple_new(string("foo", 3), string("bar", 3));
    tuple_t* value2 = tuple_new(string("fizz", 4), string("buzz", 4));

    map1 = map_set(map1, key1, value1);
    map2 = map_set(map2, key2, value2);

    TEST_ASSERT_FALSE(map_equal(map1, map2));

    map_free(map1);
    map_free(map2);
    string_free(key1);
    string_free(key2);
    string_free(value1->first);
    string_free(value1->second);
    string_free(value2->first);
    string_free(value2->second);
    tuple_free(value1);
    tuple_free(value2);
}

void test_map_equal_should_return_true_if_same_elements(void) {
    map_t* map1 = map_new(2, 8);
    map_t* map2 = map_new(2, 8);
    string_t* key = string("hello", 5);
    tuple_t* value = tuple_new(string("foo", 3), string("bar", 3));

    map1 = map_set(map1, key, value);
    map2 = map_set(map2, key, value);

    TEST_ASSERT_TRUE(map_equal(map1, map2));

    map_free(map1);
    map_free(map2);
    string_free(key);
    string_free((string_t*) value->first);
    string_free((string_t*) value->second);
    tuple_free(value);

}

void test_map_equal_should_return_true_if_same_identity(void) {
    map_t* map1 = map_new(2, 8);
    map_t* map2 = map1;

    TEST_ASSERT_TRUE(map_equal(map1, map2));

    map_free(map1);
}

void test_map_delete_should_remove_element(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("test", 4);
    tuple_t* value = tuple_new(0, 0);

    map = map_set(map, key, value);

    map_delete(map, key);
    TEST_ASSERT_EQUAL_PTR(NULL, map_get(map, key));

    map_free(map);
    string_free(key);
    tuple_free(value);
}

void test_map_delete_should_return_element_if_key_found(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("test", 4);
    tuple_t* value = tuple_new(0, 0);

    map = map_set(map, key, value);

    TEST_ASSERT_EQUAL_PTR(value, map_delete(map, key));

    map_free(map);
    string_free(key);
    tuple_free(value);
}

void test_map_delete_should_return_null_if_key_not_found(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("test", 4);

    TEST_ASSERT_EQUAL_PTR(NULL, map_delete(map, key));

    map_free(map);
    string_free(key);
}

void test_map_get_should_return_value_if_key_found(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("test", 4);
    tuple_t* value = tuple_new(string("foo", 3), string("bar", 3));

    map = map_set(map, key, value);

    TEST_ASSERT_EQUAL_PTR(value, map_get(map, key));

    map_free(map);
    string_free(key);
    string_free((string_t*) value->first);
    string_free((string_t*) value->second);
    tuple_free(value);
}

void test_map_get_should_return_null_if_key_not_found(void) {
    map_t* map = map_new(2, 8);
    string_t* key = string("test", 4);

    TEST_ASSERT_EQUAL_PTR(NULL, map_get(map, key));

    map_free(map);
    string_free(key);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_map_copy_should_return_a_new_copy);
    RUN_TEST(test_map_copy_should_not_modify_original);
    RUN_TEST(test_map_copy_should_create_copy_equal_to_original);

    RUN_TEST(test_map_clear_should_remove_all_elements);
    RUN_TEST(test_map_set_should_overwrite_old_value);
    RUN_TEST(test_map_set_should_set_key_to_value);
    
    RUN_TEST(test_map_equal_should_return_false_if_different_keys);
    RUN_TEST(test_map_equal_should_return_false_if_different_pairs);
    RUN_TEST(test_map_equal_should_return_false_if_different_values);
    RUN_TEST(test_map_equal_should_return_true_if_same_elements);
    RUN_TEST(test_map_equal_should_return_true_if_same_identity);

    RUN_TEST(test_map_delete_should_remove_element);
    RUN_TEST(test_map_delete_should_return_element_if_key_found);
    RUN_TEST(test_map_delete_should_return_null_if_key_not_found);
    RUN_TEST(test_map_get_should_return_null_if_key_not_found);
    RUN_TEST(test_map_get_should_return_value_if_key_found);

    UNITY_END();
}
