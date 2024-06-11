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

#include <fossil/mockup/spy.h> // library under test

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

FOSSIL_TEST(fossil_mockup_try_spy_create_and_erase) {
    // Create a spy object
    fossil_mockup_spy_t *spy = fossil_mockup_spy_create("test_function", 2);
    ASSUME_NOT_CNULL(spy);

    // Check the function name and number of arguments
    ASSUME_ITS_EQUAL_CSTR("test_function", spy->function_name);
    ASSUME_ITS_EQUAL_I32(2, spy->num_args);

    // Erase the spy object
    fossil_mockup_spy_erase(spy);
}

FOSSIL_TEST(fossil_mockup_try_spy_record_and_get_call_args) {
    // Create a spy object
    fossil_mockup_spy_t *spy = fossil_mockup_spy_create("test_function", 2);
    ASSUME_NOT_CNULL(spy);

    // Record a function call
    int arg1 = 42;
    char *arg2 = "test";
    fossil_mockup_spy_record_call(spy, &arg1, arg2);

    // Retrieve and verify the recorded arguments
    void **args = fossil_mockup_spy_get_call_args(spy, 0);
    ASSUME_ITS_EQUAL_I32(arg1, *(int *)args[0]);
    ASSUME_ITS_EQUAL_CSTR(arg2, (char *)args[1]);

    // Erase the spy object
    fossil_mockup_spy_erase(spy);
}

FOSSIL_TEST(fossil_mockup_try_spy_verify_call_count) {
    // Create a spy object
    fossil_mockup_spy_t *spy = fossil_mockup_spy_create("test_function", 2);
    ASSUME_NOT_CNULL(spy);

    // Record function calls
    int arg1 = 42;
    char *arg2 = "test";
    fossil_mockup_spy_record_call(spy, &arg1, arg2);
    fossil_mockup_spy_record_call(spy, &arg1, arg2);

    // Verify the call count
    ASSUME_ITS_TRUE(fossil_mockup_spy_verify_call_count(spy, 2));

    // Erase the spy object
    fossil_mockup_spy_erase(spy);
}

FOSSIL_TEST(fossil_mockup_try_spy_reset) {
    // Create a spy object
    fossil_mockup_spy_t *spy = fossil_mockup_spy_create("test_function", 2);
    ASSUME_NOT_CNULL(spy);

    // Record function calls
    int arg1 = 42;
    char *arg2 = "test";
    fossil_mockup_spy_record_call(spy, &arg1, arg2);
    fossil_mockup_spy_record_call(spy, &arg1, arg2);

    // Verify the call count
    ASSUME_ITS_TRUE(fossil_mockup_spy_verify_call_count(spy, 2));

    // Reset the spy object
    fossil_mockup_spy_reset(spy);

    // Verify the reset
    ASSUME_ITS_EQUAL_I32(0, spy->call_count);
    ASSUME_NOT_CNULL(spy->recorded_args);

    // Erase the spy object
    fossil_mockup_spy_erase(spy);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(fossil_mockup_spy_group) {
    ADD_TEST(fossil_mockup_try_spy_create_and_erase);
    ADD_TEST(fossil_mockup_try_spy_record_and_get_call_args);
    ADD_TEST(fossil_mockup_try_spy_verify_call_count);
    ADD_TEST(fossil_mockup_try_spy_reset);
} // end of fixture
