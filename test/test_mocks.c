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
#include <fossil/unittest/framework.h>   // basic test tools
#include <fossil/xassert.h> // extra asserts

#include <fossil/mockup/framework.h> // library under test

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

// Test Case for Mocking a Function
FOSSIL_TEST(mock_function_test) {
    MockCallList mock;
    MOCK_INIT(mock);

    // Simulating function calls
    char *args1[] = {"arg1", "arg2"};
    MOCK_ADD_CALL(mock, "mock_function", args1, 2);

    char *args2[] = {"arg3", "arg4"};
    MOCK_ADD_CALL(mock, "mock_function", args2, 2);

    // Validate that the calls were recorded
    printf("Mock function calls:\n");
    MOCK_PRINT(mock);

    MOCK_DESTROY(mock);
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_GROUP(test_using_mock_group) {
    ADD_TEST(mock_function_test);
}
