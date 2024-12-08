/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 07/01/2024
 *
 * Copyright (C) 2024 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/test/framework.h>
#include <string>
#include <cstring>


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_TEST_SUITE(cpp_mock_suite);

// Setup function for the test suite
FOSSIL_SETUP(cpp_mock_suite) {
    // Setup code here
}

// Teardown function for the test suite
FOSSIL_TEARDOWN(cpp_mock_suite) {
    // Teardown code here
}

FOSSIL_MOCK_ALIAS(MockInt, int);

// Example of creating a mock struct using the macro
FOSSIL_MOCK_STRUCT(MockStruct) {
    int a;
    char b;
};

// Example of creating a mock function using the macro
FOSSIL_MOCK_FUNC(int, mock_function, int a, int b) {
    return a + b;
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, showcasing
// Domain-Driven Design (DDD) usage in the Fossil Logic project.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_CASE(cpp_mock_call_list_initialization) {
    // Example of initializing a MockCallList
    MockCallList list;
    fossil_mock_init(&list);

    // Test cases
    FOSSIL_TEST_ASSUME(list.head == NULL, "MockCallList head should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.tail == NULL, "MockCallList tail should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.size == 0, "MockCallList size should be 0 after initialization");
} // end case

FOSSIL_TEST_CASE(cpp_mock_call_list_addition) {
    // Example of adding a MockCall to a MockCallList
    MockCallList list;
    fossil_mock_init(&list);
    const char* args[] = {"arg1", "arg2"};
    fossil_mock_add_call(&list, "test_function", (char**)args, 2);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "MockCallList size should be 1 after adding a call");
    //FOSSIL_TEST_ASSUME(list.head->function_name == "test_function", "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");
    FOSSIL_TEST_ASSUME(std::strcmp(list.head->arguments[0], "arg1") == 0, "First argument should be 'arg1'");
    FOSSIL_TEST_ASSUME(std::strcmp(list.head->arguments[1], "arg2") == 0, "Second argument should be 'arg2'");
} // end case

FOSSIL_TEST_CASE(cpp_mock_call_list_destruction) {
    // Example of destroying a MockCallList
    MockCallList list;
    fossil_mock_init(&list);
    const char* args[] = {"arg1", "arg2"};
    fossil_mock_add_call(&list, "test_function", (char**)args, 2);
    FOSSIL_TEST_ASSUME(list.size == 1, "MockCallList size should be 1 after adding a call");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "test_function") == 0, "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");
  
    fossil_mock_destroy(&list); // not allowed to access due to the object being freed
} // end case

FOSSIL_TEST_CASE(cpp_mock_call_list_initialization_macro) {
    // Example of initializing a MockCallList using the macro
    MockCallList list;
    MOCK_INIT(list);

    // Test cases
    FOSSIL_TEST_ASSUME(list.head == NULL, "MockCallList head should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.tail == NULL, "MockCallList tail should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.size == 0, "MockCallList size should be 0 after initialization");
} // end case

FOSSIL_TEST_CASE(cpp_mock_call_list_addition_macro) {
    // Example of adding a MockCall to a MockCallList using the macro
    MockCallList list;
    MOCK_INIT(list);
    const char* args[] = {"arg1", "arg2"};
    MOCK_ADD_CALL(list, "test_function", (char**)args, 2);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "MockCallList size should be 1 after adding a call");
    //FOSSIL_TEST_ASSUME(list.head->function_name == "test_function", "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");
    FOSSIL_TEST_ASSUME(std::strcmp(list.head->arguments[0], "arg1") == 0, "First argument should be 'arg1'");
    FOSSIL_TEST_ASSUME(std::strcmp(list.head->arguments[1], "arg2") == 0, "Second argument should be 'arg2'");
} // end case

FOSSIL_TEST_CASE(cpp_mock_call_list_destruction_macro) {
    // Example of destroying a MockCallList using the macro
    MockCallList list;
    MOCK_INIT(list);
    const char* args[] = {"arg1", "arg2"};
    MOCK_ADD_CALL(list, "test_function", (char**)args, 2);
    FOSSIL_TEST_ASSUME(list.size == 1, "MockCallList size should be 1 after adding a call");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "test_function") == 0, "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");

    MOCK_DESTROY(list); // not allowed to access due to the object being freed
} // end case

FOSSIL_TEST_CASE(cpp_mock_function_creation) {
    // Test cases
    FOSSIL_TEST_ASSUME(fossil_mockup_mock_function(2, 3) == 5, "Mock function should return the sum of its arguments");
} // end case

FOSSIL_TEST_CASE(cpp_mock_alias_creation) {
    // Example of creating a type alias using the macro
    

    // Test cases
    MockInt x = 10;
    FOSSIL_TEST_ASSUME(x == 10, "Mock alias should behave like the original type");
} // end case

FOSSIL_TEST_CASE(cpp_mock_struct_creation) {
    // Test cases
    MockStruct instance;
    instance.a = 5;
    instance.b = 'c';
    FOSSIL_TEST_ASSUME(instance.a == 5, "Mock struct member 'a' should be 5");
    FOSSIL_TEST_ASSUME(instance.b == 'c', "Mock struct member 'b' should be 'c'");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mock_test_cases) {
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_initialization);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_addition);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_destruction);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_initialization_macro);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_addition_macro);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_destruction_macro);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_function_creation);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_alias_creation);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_struct_creation);

    FOSSIL_TEST_REGISTER(cpp_mock_suite);
} // end of group
