#include "unity.h"

#include "cstrings.h"
#include "tuple.h"

void setUp(void) {}

void tearDown(void) {}

void test_tuple_copy_should_return_new_identity_with_same_elements(void) {
    tuple_t* original = tuple_new("hello", "world");
    tuple_t* copy = tuple_copy(original);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(original->first, copy->first, 5);
    TEST_ASSERT_EQUAL_CHAR_ARRAY(original->second, copy->second, 5);

    tuple_free(original);
    tuple_free(copy);
}

void test_tuple_equal_should_return_true_if_same_identity(void) {
    tuple_t* original = tuple_new("hello", "world");
    tuple_t* copy = original;

    TEST_ASSERT_TRUE(tuple_equal(original, copy));

    tuple_free(original);
}

void test_tuple_equal_should_return_true_if_same_elements(void) {
    string_t* first = string("hello", 5);
    string_t* second = string("world", 5);
    tuple_t* original = tuple_new(first, second);
    tuple_t* copy = tuple_copy(original);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_TRUE(tuple_equal(original, copy));

    tuple_free(original);
    tuple_free(copy);
    string_free(first);
    string_free(second);
}

void test_tuple_equal_should_return_false_if_differing_elements(void) {
    tuple_t* lhs = tuple_new("hello", "world");
    tuple_t* rhs = tuple_new("goodbye", "world");

    TEST_ASSERT_FALSE(tuple_equal(lhs, rhs));

    tuple_free(lhs);
    tuple_free(rhs);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_tuple_copy_should_return_new_identity_with_same_elements);
    RUN_TEST(test_tuple_equal_should_return_false_if_differing_elements);
    RUN_TEST(test_tuple_equal_should_return_true_if_same_elements);
    RUN_TEST(test_tuple_equal_should_return_true_if_same_identity);

    UNITY_END();
}
