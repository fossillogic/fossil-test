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

#include <fossil/mockup/input.h> // library under test

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// placeholder

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, inspired
// by the Meson build system's approach of using test cases
// as samples for library usage.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(fossil_mockup_try_input_create_and_erase) {
    // Create an input mock object
    fossil_mockup_input_t *input = fossil_mockup_input_create("test_function");
    ASSUME_NOT_CNULL(input);

    // Check the function name
    ASSUME_ITS_EQUAL_CSTR("test_function", input->function_name);

    // Erase the input mock object
    fossil_mockup_input_erase(input);
}

FOSSIL_TEST(fossil_mockup_try_input_set_and_get) {
    // Create an input mock object
    fossil_mockup_input_t *input = fossil_mockup_input_create("test_function");
    ASSUME_NOT_CNULL(input);

    // Set mocked inputs
    int mocked_input1 = 42;
    int mocked_input2 = 24;
    fossil_mockup_input_set_inputs(input, 2, &mocked_input1, &mocked_input2);

    // Get mocked inputs
    int *retrieved_input1 = (int *)fossil_mockup_input_get(input);
    ASSUME_ITS_EQUAL_PTR(&mocked_input1, retrieved_input1);

    int *retrieved_input2 = (int *)fossil_mockup_input_get(input);
    ASSUME_ITS_EQUAL_PTR(&mocked_input2, retrieved_input2);

    // Erase the input mock object
    fossil_mockup_input_erase(input);
}

FOSSIL_TEST(fossil_mockup_try_input_verify_call_count) {
    // Create an input mock object
    fossil_mockup_input_t *input = fossil_mockup_input_create("test_function");
    ASSUME_NOT_CNULL(input);

    // Set mocked inputs
    int mocked_input = 42;
    fossil_mockup_input_set_inputs(input, 1, &mocked_input);

    // Simulate function calls
    fossil_mockup_input_get(input);
    fossil_mockup_input_get(input);

    // Verify call count
    bool is_call_count_correct = fossil_mockup_input_verify_call_count(input, 2);
    ASSUME_ITS_TRUE(is_call_count_correct);

    // Erase the input mock object
    fossil_mockup_input_erase(input);
}

FOSSIL_TEST(fossil_mockup_try_input_reset) {
    // Create an input mock object
    fossil_mockup_input_t *input = fossil_mockup_input_create("test_function");
    ASSUME_NOT_CNULL(input);

    // Set mocked inputs
    int mocked_input = 42;
    fossil_mockup_input_set_inputs(input, 1, &mocked_input);

    // Simulate a function call
    fossil_mockup_input_get(input);

    // Reset the input mock object
    fossil_mockup_input_reset(input);

    // Verify that the call count is reset
    bool is_call_count_correct = fossil_mockup_input_verify_call_count(input, 0);
    ASSUME_ITS_TRUE(is_call_count_correct);

    // Erase the input mock object
    fossil_mockup_input_erase(input);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fossil_mockup_input_group) {
    ADD_TEST(fossil_mockup_try_input_create_and_erase);
    ADD_TEST(fossil_mockup_try_input_set_and_get);
    ADD_TEST(fossil_mockup_try_input_verify_call_count);
    ADD_TEST(fossil_mockup_try_input_reset);
} // end of fixture
