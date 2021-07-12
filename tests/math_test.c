#include "unity.h"

#include "math.h"

void setUp(void) {}

void tearDown(void) {}

void test_math_min_returns_lhs_if_lhs_less_than_rhs(void) {
    TEST_ASSERT_EQUAL(0, crumb_min(0, 1));
}

void test_math_min_returns_rhs_if_rhs_less_than_lhs(void) {
    TEST_ASSERT_EQUAL(0, crumb_min(1, 0));
}

void test_math_min_returns_same_value_if_lhs_equals_rhs(void) {
    TEST_ASSERT_EQUAL(4, crumb_min(4, 4));
}

void test_math_max_returns_rhs_if_rhs_greater_than_lhs(void) {
    TEST_ASSERT_EQUAL(1, crumb_max(0, 1));
}

void test_math_max_returns_lhs_if_lhs_greater_than_rhs(void) {
    TEST_ASSERT_EQUAL(1, crumb_max(1, 0));
}

void test_math_max_returns_same_value_if_lhs_equals_rhs(void) {
    TEST_ASSERT_EQUAL(4, crumb_max(4, 4));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_math_min_returns_lhs_if_lhs_less_than_rhs);
    RUN_TEST(test_math_min_returns_rhs_if_rhs_less_than_lhs);
    RUN_TEST(test_math_min_returns_same_value_if_lhs_equals_rhs);
    RUN_TEST(test_math_max_returns_lhs_if_lhs_greater_than_rhs);
    RUN_TEST(test_math_max_returns_rhs_if_rhs_greater_than_lhs);
    RUN_TEST(test_math_max_returns_same_value_if_lhs_equals_rhs);

    UNITY_END();
}
