/*
==============================================================================
Author: Michael Gene Brockus (Dreamer)
Email: michaelbrockus@gmail.com
Organization: Fossil Logic
Description: 
    This file is part of the Fossil Logic project, where innovation meets
    excellence in software development. Michael Gene Brockus, also known as
    "Dreamer," is a dedicated contributor to this project. For any inquiries,
    feel free to contact Michael at michaelbrockus@gmail.com.
==============================================================================
*/
#include <fossil/unittest.h>   // basic test tools
#include <fossil/xassume.h> // extra asserts

#include <fossil/mockup.h>   // library under test

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(fossil_mockup_try_create_and_erase) {
    // Create a mock object
    fossil_mockup_t *mock = fossil_mockup_create("test_function", 2);
    ASSUME_NOT_CNULL(mock);

    // Check the function name and number of arguments
    ASSUME_ITS_EQUAL_CSTR("test_function", mock->function_name);
    ASSUME_ITS_EQUAL_I32(2, mock->num_args);

    // Erase the mock object
    fossil_mockup_erase(mock);
}

FOSSIL_TEST(fossil_mockup_try_set_expected_args_and_call) {
    // Create a mock object
    fossil_mockup_t *mock = fossil_mockup_create("test_function", 2);
    ASSUME_NOT_CNULL(mock);

    // Set expected arguments
    int expected_arg1 = 42;
    char *expected_arg2 = "expected";
    fossil_mockup_set_expected_args(mock, &expected_arg1, expected_arg2);

    // Set return value
    int return_value = 99;
    fossil_mockup_set_return_values(mock, 1, &return_value);

    // Simulate calling the mock function
    int *ret_val = (int *)fossil_mockup_call(mock, &expected_arg1, expected_arg2);
    ASSUME_ITS_EQUAL_I32(return_value, *ret_val);

    // Verify the call
    ASSUME_ITS_TRUE(fossil_mockup_verify(mock));

    // Erase the mock object
    fossil_mockup_erase(mock);
}

FOSSIL_TEST(fossil_mockup_try_set_comparator_and_verify) {
    // Create a mock object
    fossil_mockup_t *mock = fossil_mockup_create("test_function", 2);
    ASSUME_NOT_CNULL(mock);

    // Set expected arguments
    int expected_arg1 = 42;
    char *expected_arg2 = "expected";
    fossil_mockup_set_expected_args(mock, &expected_arg1, expected_arg2);

    // Set custom comparator for the second argument
    fossil_mockup_set_comparator(mock, 1, fossil_mockup_cstr_comparator);

    // Set return value
    int return_value = 99;
    fossil_mockup_set_return_values(mock, 1, &return_value);

    // Simulate calling the mock function
    int *ret_val = (int *)fossil_mockup_call(mock, &expected_arg1, "expected");
    ASSUME_ITS_EQUAL_I32(return_value, *ret_val);

    // Verify the call
    ASSUME_ITS_TRUE(fossil_mockup_verify(mock));

    // Erase the mock object
    fossil_mockup_erase(mock);
}

FOSSIL_TEST(fossil_mockup_try_verify_call_count) {
    // Create a mock object
    fossil_mockup_t *mock = fossil_mockup_create("test_function", 2);
    ASSUME_NOT_CNULL(mock);

    // Set expected arguments
    int expected_arg1 = 42;
    char *expected_arg2 = "expected";
    fossil_mockup_set_expected_args(mock, &expected_arg1, expected_arg2);

    // Set return value
    int return_value = 99;
    fossil_mockup_set_return_values(mock, 1, &return_value);

    // Simulate calling the mock function twice
    fossil_mockup_call(mock, &expected_arg1, expected_arg2);
    fossil_mockup_call(mock, &expected_arg1, expected_arg2);

    // Verify the call count
    ASSUME_ITS_TRUE(fossil_mockup_verify_call_count(mock, 2));
    ASSUME_ITS_FALSE(fossil_mockup_verify_call_count(mock, 1));

    // Erase the mock object
    fossil_mockup_erase(mock);
}

FOSSIL_TEST(fossil_mockup_try_reset) {
    // Create a mock object
    fossil_mockup_t *mock = fossil_mockup_create("test_function", 2);
    ASSUME_NOT_CNULL(mock);

    // Set expected arguments
    int expected_arg1 = 42;
    char *expected_arg2 = "expected";
    fossil_mockup_set_expected_args(mock, &expected_arg1, expected_arg2);

    // Set return value
    int return_value = 99;
    fossil_mockup_set_return_values(mock, 1, &return_value);

    // Simulate calling the mock function
    fossil_mockup_call(mock, &expected_arg1, expected_arg2);

    // Verify the call
    ASSUME_ITS_TRUE(fossil_mockup_verify(mock));

    // Reset the mock object
    fossil_mockup_reset(mock);

    // Verify the reset
    ASSUME_ITS_FALSE(mock->called);
    ASSUME_ITS_EQUAL_I32(0, mock->call_count);

    // Erase the mock object
    fossil_mockup_erase(mock);
}

// Built-in comparators for common data types
FOSSIL_TEST(fossil_mockup_try_i32_comparator) {
    int32_t a = 42;
    int32_t b = 42;
    int32_t c = 24;
    ASSUME_ITS_TRUE(fossil_mockup_i32_comparator(&a, &b));
    ASSUME_ITS_FALSE(fossil_mockup_i32_comparator(&a, &c));
}

FOSSIL_TEST(fossil_mockup_try_cstr_comparator) {
    const char *str1 = "test";
    const char *str2 = "test";
    const char *str3 = "diff";
    ASSUME_ITS_TRUE(fossil_mockup_cstr_comparator((void *)str1, (void *)str2));
    ASSUME_ITS_FALSE(fossil_mockup_cstr_comparator((void *)str1, (void *)str3));
}

FOSSIL_TEST(fossil_mockup_try_pointer_comparator) {
    int a = 42;
    int b = 42;
    ASSUME_ITS_TRUE(fossil_mockup_ptr_comparator(&a, &a));
    ASSUME_ITS_FALSE(fossil_mockup_ptr_comparator(&a, &b));
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fossil_mockup_group) {
    ADD_TEST(fossil_mockup_try_create_and_erase);
    ADD_TEST(fossil_mockup_try_set_expected_args_and_call);
    ADD_TEST(fossil_mockup_try_set_comparator_and_verify);
    ADD_TEST(fossil_mockup_try_verify_call_count);
    ADD_TEST(fossil_mockup_try_reset);
    ADD_TEST(fossil_mockup_try_i32_comparator);
    ADD_TEST(fossil_mockup_try_cstr_comparator);
    ADD_TEST(fossil_mockup_try_pointer_comparator);
} // end of fixture
