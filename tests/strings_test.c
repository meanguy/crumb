#include "unity.h"

#include "strings.h"

void setUp(void) {}

void tearDown(void) {}

void test_string_copy_should_create_a_new_copy(void) {
    string_t* original = string("test", 4);
    string_t* copy = string_copy(original);

    TEST_ASSERT_NOT_EQUAL(original, copy);
    TEST_ASSERT_TRUE(string_equal(original, copy));

    string_free(original);
    string_free(copy);
}

void test_string_equal_should_return_true_for_same_identity(void) {
    string_t* lhs = string("test", 4);
    string_t* rhs = lhs;

    TEST_ASSERT_TRUE(string_equal(lhs, rhs));

    string_free(lhs);
}

void test_string_equal_should_return_true_for_same_data(void) {
    string_t* lhs = string("test", 4);
    string_t* rhs = string("test", 4);

    TEST_ASSERT_TRUE(string_equal(lhs, rhs));

    string_free(lhs);
    string_free(rhs);
}

void test_string_equal_should_return_false_for_differing_data(void) {
    string_t* lhs = string("hello", 5);
    string_t* rhs = string("world", 5);

    TEST_ASSERT_FALSE(string_equal(lhs, rhs));

    string_free(lhs);
    string_free(rhs);
}

void test_string_data_should_return_original_char_array(void) {
    string_t* str = string("hello", 5);

    TEST_ASSERT_EQUAL_CHAR_ARRAY("hello", string_data(str), 5);

    string_free(str);
}

void test_string_length_should_return_original_length(void) {
    string_t* str = string("test", 4);

    TEST_ASSERT_EQUAL(4, string_length(str));

    string_free(str);
}

void test_string_substr_should_return_null_if_start_negative(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, -1, 2);

    TEST_ASSERT_EQUAL_PTR(NULL, substr);

    string_free(str);
}

void test_string_substr_should_return_null_if_end_negative(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, 0, -1);

    TEST_ASSERT_EQUAL_PTR(NULL, substr);

    string_free(str);
}

void test_string_substr_should_return_null_if_start_after_end(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, 2, 0);

    TEST_ASSERT_EQUAL_PTR(NULL, substr);
    
    string_free(str);
}

void test_string_substr_should_return_substring_of_original_start(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, 0, 2);

    TEST_ASSERT_EQUAL_CHAR_ARRAY("abc", string_data(substr), 3);

    string_free(str);
    string_free(substr);
}

void test_string_substr_should_return_substring_of_original_middle(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, 2, 4);

    TEST_ASSERT_EQUAL_CHAR_ARRAY("cde", string_data(substr), 3);

    string_free(str);
    string_free(substr);
}

void test_string_substr_should_return_substring_of_original_end(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, 3, 5);

    TEST_ASSERT_EQUAL_CHAR_ARRAY("def", string_data(substr), 3);

    string_free(str);
    string_free(substr);
}

void test_string_substr_should_return_substring_of_original_whole(void) {
    string_t* str = string("abcdef", 6);
    string_t* substr = string_substr(str, 0, 5);

    TEST_ASSERT_NOT_EQUAL(str, substr);
    TEST_ASSERT_EQUAL_CHAR_ARRAY("abcdef", string_data(substr), 6);

    string_free(str);
    string_free(substr);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_string_copy_should_create_a_new_copy);
    RUN_TEST(test_string_equal_should_return_true_for_same_data);
    RUN_TEST(test_string_equal_should_return_true_for_same_identity);
    RUN_TEST(test_string_equal_should_return_false_for_differing_data);
    RUN_TEST(test_string_data_should_return_original_char_array);
    RUN_TEST(test_string_length_should_return_original_length);
    RUN_TEST(test_string_substr_should_return_null_if_start_after_end);
    RUN_TEST(test_string_substr_should_return_null_if_start_negative);
    RUN_TEST(test_string_substr_should_return_substring_of_original_end);
    RUN_TEST(test_string_substr_should_return_substring_of_original_middle);
    RUN_TEST(test_string_substr_should_return_substring_of_original_start);
    RUN_TEST(test_string_substr_should_return_substring_of_original_whole);

    UNITY_END();
}
