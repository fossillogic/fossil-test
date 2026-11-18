/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/maip/framework.h>
#include <string.h>


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(c_mock_suite);

// Setup function for the test suite
FOSSIL_SETUP(c_mock_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(c_mock_suite) {
    // Teardown code here
}

FOSSIL_MOCK_ALIAS(MockInt, int);

// Example of creating a mock struct using the macro
FOSSIL_MOCK_STRUCT(MockStruct) {
    int a;
    char b;
} MockStruct;

// Example of creating a mock function using the macro
FOSSIL_MOCK_FUNC(int, c_mock_function, int a, int b) {
    return a + b;
}

FOSSIL_MOCK_FUNC(void, c_mock_function_with_output, void) {
    maip_io_printf("Hello, Fossil Logic!");
}

FOSSIL_MOCK_FUNC(void, mock_function_redirection, void) {
    maip_io_printf("Testing macro redirection!");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, showcasing
// Domain-Driven Design (DDD) usage in the Fossil Logic project.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(c_mock_call_list_initialization) {
    // Example of initializing a fossil_mock_calllist_t using macro
    fossil_mock_calllist_t list;
    MOCK_INIT(list);

    // Test cases
    FOSSIL_TEST_ASSUME(list.head == NULL, "fossil_mock_calllist_t head should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.tail == NULL, "fossil_mock_calllist_t tail should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.size == 0, "fossil_mock_calllist_t size should be 0 after initialization");
} // end case

FOSSIL_TEST(c_mock_io_capture_output) {
    // Buffer to capture output
    char buffer[256];

    // Capture the output of the mock function
    int captured_size = fossil_mock_capture_output(buffer, sizeof(buffer), MOCK_FUNC_CALL(c_mock_function_with_output));

    // Test cases
    FOSSIL_TEST_ASSUME(captured_size > 0, "Captured size should be greater than 0");
    FOSSIL_TEST_ASSUME(strcmp(buffer, "Hello, Fossil Logic!") == 0, "Captured output should match expected output");
} // end case

FOSSIL_TEST(c_mock_io_compare_output) {
    // Captured and expected outputs
    const char *captured = "Hello, Fossil Logic!";
    const char *expected = "Hello, Fossil Logic!";

    // Compare the outputs
    bool result = fossil_mock_compare_output(captured, expected);

    // Test cases
    FOSSIL_TEST_ASSUME(result == true, "Captured output should match expected output");
} // end case

FOSSIL_TEST(c_mock_io_redirect_stdout_macro) {
    // Buffer to capture output
    char buffer[256];

    // Use the macro to redirect stdout and capture output
    FOSSIL_MOCK_REDIRECT_STDOUT(buffer, sizeof(buffer), fossil_mockup_mock_function_redirection);

    // Test cases
    FOSSIL_TEST_ASSUME(strcmp(buffer, "Testing macro redirection!") == 0, "Captured output should match expected output");
} // end case

FOSSIL_TEST(c_mock_io_compare_output_macro) {
    // Captured and expected outputs
    const char *captured = "Macro comparison test!";
    const char *expected = "Macro comparison test!";

    // Use the macro to compare outputs
    bool result = FOSSIL_MOCK_COMPARE_OUTPUT(captured, expected);

    // Test cases
    FOSSIL_TEST_ASSUME(result == true, "Captured output should match expected output using macro");
} // end case

//

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(c_mock_test_cases) {
    FOSSIL_ADD_TEST(c_mock_suite, c_mock_call_list_initialization);
    FOSSIL_ADD_TEST(c_mock_suite, c_mock_io_capture_output);
    FOSSIL_ADD_TEST(c_mock_suite, c_mock_io_compare_output);
    FOSSIL_ADD_TEST(c_mock_suite, c_mock_io_redirect_stdout_macro);
    FOSSIL_ADD_TEST(c_mock_suite, c_mock_io_compare_output_macro);
    FOSSIL_ADD_TEST(c_mock_suite, c_mock_io_compare_output);

    FOSSIL_ADD_SUITE(c_mock_suite);
} // end of group
