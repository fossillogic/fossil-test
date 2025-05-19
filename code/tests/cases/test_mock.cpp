/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include <fossil/pizza/framework.h>
#include <string.h>


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilites
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

// Define the test suite and add test cases
FOSSIL_SUITE(cpp_mock_suite);

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
FOSSIL_MOCK_FUNC(int, cpp_mock_function, int a, int b) {
    return a + b;
}

FOSSIL_MOCK_FUNC(void, cpp_mock_function_with_output, void) {
    pizza_io_printf("Hello, Fossil Logic!");
}

FOSSIL_MOCK_FUNC(void, mock_function_redirection, void) {
    pizza_io_printf("Testing macro redirection!");
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Cases
// * * * * * * * * * * * * * * * * * * * * * * * *
// The test cases below are provided as samples, showcasing
// Domain-Driven Design (DDD) usage in the Fossil Logic project.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST(cpp_mock_call_list_initialization) {
    // Example of initializing a fossil_mock_calllist_t
    fossil_mock_calllist_t list;
    fossil_mock_init(&list);

    // Test cases
    FOSSIL_TEST_ASSUME(list.head == NULL, "fossil_mock_calllist_t head should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.tail == NULL, "fossil_mock_calllist_t tail should be NULL after initialization");
    FOSSIL_TEST_ASSUME(list.size == 0, "fossil_mock_calllist_t size should be 0 after initialization");
} // end case

FOSSIL_TEST(cpp_mock_call_list_addition) {
    // Example of adding a fossil_mock_call_t to a fossil_mock_calllist_t
    fossil_mock_calllist_t list;
    fossil_mock_init(&list);

    // Create mock arguments
    fossil_mock_pizza_t args[2];
    args[0].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[0].value.data = pizza_io_cstr_dup("arg1");
    args[0].value.mutable_flag = false;
    args[0].attribute.name = pizza_io_cstr_dup("arg1_name");
    args[0].attribute.description = pizza_io_cstr_dup("First argument");
    args[0].attribute.id = pizza_io_cstr_dup("1");

    args[1].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[1].value.data = pizza_io_cstr_dup("arg2");
    args[1].value.mutable_flag = false;
    args[1].attribute.name = pizza_io_cstr_dup("arg2_name");
    args[1].attribute.description = pizza_io_cstr_dup("Second argument");
    args[1].attribute.id = pizza_io_cstr_dup("2");

    fossil_mock_add_call(&list, "test_function", args, 2);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "fossil_mock_calllist_t size should be 1 after adding a call");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "test_function") == 0, "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[0].value.data, "arg1") == 0, "First argument should be 'arg1'");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[1].value.data, "arg2") == 0, "Second argument should be 'arg2'");
} // end case

FOSSIL_TEST(cpp_mock_call_list_destruction) {
    // Example of destroying a fossil_mock_calllist_t
    fossil_mock_calllist_t list;
    fossil_mock_init(&list);

    // Create mock arguments
    fossil_mock_pizza_t args[2];
    args[0].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[0].value.data = pizza_io_cstr_dup("arg1");
    args[0].value.mutable_flag = false;
    args[0].attribute.name = pizza_io_cstr_dup("arg1_name");
    args[0].attribute.description = pizza_io_cstr_dup("First argument");
    args[0].attribute.id = pizza_io_cstr_dup("1");

    args[1].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[1].value.data = pizza_io_cstr_dup("arg2");
    args[1].value.mutable_flag = false;
    args[1].attribute.name = pizza_io_cstr_dup("arg2_name");
    args[1].attribute.description = pizza_io_cstr_dup("Second argument");
    args[1].attribute.id = pizza_io_cstr_dup("2");

    fossil_mock_add_call(&list, "test_function", args, 2);

    FOSSIL_TEST_ASSUME(list.size == 1, "fossil_mock_calllist_t size should be 1 after adding a call");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "test_function") == 0, "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");

    fossil_mock_destroy(&list);
} // end case

FOSSIL_TEST(cpp_mock_function_creation) {
    // Test cases
    FOSSIL_TEST_ASSUME(fossil_mockup_cpp_mock_function(2, 3) == 5, "Mock function should return the sum of its arguments");
} // end case

FOSSIL_TEST(cpp_mock_alias_creation) {
    // Example of creating a type alias using the macro

    // Test cases
    MockInt x = 10;
    FOSSIL_TEST_ASSUME(x == 10, "Mock alias should behave like the original type");
} // end case

FOSSIL_TEST(cpp_mock_struct_creation) {
    // Test cases
    MockStruct instance;
    instance.a = 5;
    instance.b = 'c';
    FOSSIL_TEST_ASSUME(instance.a == 5, "Mock struct member 'a' should be 5");
    FOSSIL_TEST_ASSUME(instance.b == 'c', "Mock struct member 'b' should be 'c'");
} // end case

FOSSIL_TEST(cpp_mock_call_list_type_handling) {
    // Initialize the mock call list
    fossil_mock_calllist_t list;
    fossil_mock_init(&list);

    // Create mock arguments with various types
    fossil_mock_pizza_t args[3];
    args[0].type = FOSSIL_MOCK_PIZZA_TYPE_I32;
    args[0].value.data = pizza_io_cstr_dup("42");
    args[0].value.mutable_flag = false;
    args[0].attribute.name = pizza_io_cstr_dup("arg1");
    args[0].attribute.description = pizza_io_cstr_dup("Integer argument");
    args[0].attribute.id = pizza_io_cstr_dup("1");

    args[1].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[1].value.data = pizza_io_cstr_dup("Hello");
    args[1].value.mutable_flag = true;
    args[1].attribute.name = pizza_io_cstr_dup("arg2");
    args[1].attribute.description = pizza_io_cstr_dup("String argument");
    args[1].attribute.id = pizza_io_cstr_dup("2");

    args[2].type = FOSSIL_MOCK_PIZZA_TYPE_BOOL;
    args[2].value.data = pizza_io_cstr_dup("true");
    args[2].value.mutable_flag = false;
    args[2].attribute.name = pizza_io_cstr_dup("arg3");
    args[2].attribute.description = pizza_io_cstr_dup("Boolean argument");
    args[2].attribute.id = pizza_io_cstr_dup("3");

    // Add a mock call with the arguments
    fossil_mock_add_call(&list, "test_function", args, 3);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "fossil_mock_calllist_t size should be 1 after adding a call");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "test_function") == 0, "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 3, "Number of arguments should be 3");

    FOSSIL_TEST_ASSUME(list.head->arguments[0].type == FOSSIL_MOCK_PIZZA_TYPE_I32, "First argument type should be I32");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[0].value.data, "42") == 0, "First argument value should be '42'");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[0].attribute.name, "arg1") == 0, "First argument name should be 'arg1'");

    FOSSIL_TEST_ASSUME(list.head->arguments[1].type == FOSSIL_MOCK_PIZZA_TYPE_CSTR, "Second argument type should be CSTR");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[1].value.data, "Hello") == 0, "Second argument value should be 'Hello'");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[1].attribute.name, "arg2") == 0, "Second argument name should be 'arg2'");

    FOSSIL_TEST_ASSUME(list.head->arguments[2].type == FOSSIL_MOCK_PIZZA_TYPE_BOOL, "Third argument type should be BOOL");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[2].value.data, "true") == 0, "Third argument value should be 'true'");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[2].attribute.name, "arg3") == 0, "Third argument name should be 'arg3'");

    // Clean up
    fossil_mock_destroy(&list);
} // end case

FOSSIL_TEST(cpp_mock_call_list_edge_cases) {
    // Initialize the mock call list
    fossil_mock_calllist_t list;
    fossil_mock_init(&list);

    // Add a call with no arguments
    fossil_mock_add_call(&list, "no_args_function", NULL, 0);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "fossil_mock_calllist_t size should be 1 after adding a call with no arguments");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "no_args_function") == 0, "Function name should be 'no_args_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 0, "Number of arguments should be 0");

    // Clean up
    fossil_mock_destroy(&list);
} // end case

FOSSIL_TEST(cpp_mock_call_list_large_arguments) {
    // Initialize the mock call list
    fossil_mock_calllist_t list;
    fossil_mock_init(&list);

    // Create a large number of mock arguments
    const int num_args = 100;
    fossil_mock_pizza_t args[num_args];
    for (int i = 0; i < num_args; ++i) {
        args[i].type = FOSSIL_MOCK_PIZZA_TYPE_I32;
        args[i].value.data = pizza_io_cstr_dup("42");
        args[i].value.mutable_flag = false;
        args[i].attribute.name = pizza_io_cstr_dup("arg");
        args[i].attribute.description = pizza_io_cstr_dup("Large argument test");
        args[i].attribute.id = pizza_io_cstr_dup("id");
    }

    // Add a mock call with the large number of arguments
    fossil_mock_add_call(&list, "large_args_function", args, num_args);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "fossil_mock_calllist_t size should be 1 after adding a call with large arguments");
    FOSSIL_TEST_ASSUME(list.head->num_args == num_args, "Number of arguments should match the large number");

    // Clean up
    fossil_mock_destroy(&list);
} // end case

FOSSIL_TEST(cpp_mock_macro_initialization) {
    // Initialize the mock call list using the macro
    fossil_mock_calllist_t list;
    MOCK_INIT(list);

    // Test cases
    FOSSIL_TEST_ASSUME(list.head == NULL, "fossil_mock_calllist_t head should be NULL after initialization using macro");
    FOSSIL_TEST_ASSUME(list.tail == NULL, "fossil_mock_calllist_t tail should be NULL after initialization using macro");
    FOSSIL_TEST_ASSUME(list.size == 0, "fossil_mock_calllist_t size should be 0 after initialization using macro");
} // end case

FOSSIL_TEST(cpp_mock_macro_addition) {
    // Initialize the mock call list using the macro
    fossil_mock_calllist_t list;
    MOCK_INIT(list);

    // Create mock arguments
    fossil_mock_pizza_t args[2];
    args[0].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[0].value.data = pizza_io_cstr_dup("arg1");
    args[0].value.mutable_flag = false;
    args[0].attribute.name = pizza_io_cstr_dup("arg1_name");
    args[0].attribute.description = pizza_io_cstr_dup("First argument");
    args[0].attribute.id = pizza_io_cstr_dup("1");

    args[1].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[1].value.data = pizza_io_cstr_dup("arg2");
    args[1].value.mutable_flag = false;
    args[1].attribute.name = pizza_io_cstr_dup("arg2_name");
    args[1].attribute.description = pizza_io_cstr_dup("Second argument");
    args[1].attribute.id = pizza_io_cstr_dup("2");

    // Add a mock call using the macro
    MOCK_ADD_CALL(list, "test_function", args, 2);

    // Test cases
    FOSSIL_TEST_ASSUME(list.size == 1, "fossil_mock_calllist_t size should be 1 after adding a call using macro");
    FOSSIL_TEST_ASSUME(strcmp(list.head->function_name, "test_function") == 0, "Function name should be 'test_function'");
    FOSSIL_TEST_ASSUME(list.head->num_args == 2, "Number of arguments should be 2");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[0].value.data, "arg1") == 0, "First argument should be 'arg1'");
    FOSSIL_TEST_ASSUME(strcmp(list.head->arguments[1].value.data, "arg2") == 0, "Second argument should be 'arg2'");
} // end case

FOSSIL_TEST(cpp_mock_macro_destruction) {
    // Initialize the mock call list using the macro
    fossil_mock_calllist_t list;
    MOCK_INIT(list);

    // Create mock arguments
    fossil_mock_pizza_t args[2];
    args[0].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[0].value.data = pizza_io_cstr_dup("arg1");
    args[0].value.mutable_flag = false;
    args[0].attribute.name = pizza_io_cstr_dup("arg1_name");
    args[0].attribute.description = pizza_io_cstr_dup("First argument");
    args[0].attribute.id = pizza_io_cstr_dup("1");

    args[1].type = FOSSIL_MOCK_PIZZA_TYPE_CSTR;
    args[1].value.data = pizza_io_cstr_dup("arg2");
    args[1].value.mutable_flag = false;
    args[1].attribute.name = pizza_io_cstr_dup("arg2_name");
    args[1].attribute.description = pizza_io_cstr_dup("Second argument");
    args[1].attribute.id = pizza_io_cstr_dup("2");

    // Add a mock call using the macro
    MOCK_ADD_CALL(list, "test_function", args, 2);

    // Destroy the mock call list using the macro
    MOCK_DESTROY(list);

    // Test cases
    FOSSIL_TEST_ASSUME(list.head == NULL, "fossil_mock_calllist_t head should be NULL after destruction using macro");
    FOSSIL_TEST_ASSUME(list.tail == NULL, "fossil_mock_calllist_t tail should be NULL after destruction using macro");
    FOSSIL_TEST_ASSUME(list.size == 0, "fossil_mock_calllist_t size should be 0 after destruction using macro");
} // end case

FOSSIL_TEST(cpp_mock_io_capture_output) {
    // Buffer to capture output
    char buffer[256];

    // Capture the output of the mock function
    int captured_size = fossil_mock_capture_output(buffer, sizeof(buffer), fossil_mockup_cpp_mock_function_with_output);

    // Test cases
    FOSSIL_TEST_ASSUME(captured_size > 0, "Captured size should be greater than 0");
    FOSSIL_TEST_ASSUME(strcmp(buffer, "Hello, Fossil Logic!") == 0, "Captured output should match expected output");
} // end case

FOSSIL_TEST(cpp_mock_io_compare_output) {
    // Captured and expected outputs
    const char *captured = "Hello, Fossil Logic!";
    const char *expected = "Hello, Fossil Logic!";

    // Compare the outputs
    bool result = fossil_mock_compare_output(captured, expected);

    // Test cases
    FOSSIL_TEST_ASSUME(result == true, "Captured output should match expected output");
} // end case

FOSSIL_TEST(cpp_mock_io_redirect_stdout_macro) {
    // Buffer to capture output
    char buffer[256];

    // Use the macro to redirect stdout and capture output
    FOSSIL_MOCK_REDIRECT_STDOUT(buffer, sizeof(buffer), fossil_mockup_mock_function_redirection, NULL);

    // Test cases
    FOSSIL_TEST_ASSUME(strcmp(buffer, "Testing macro redirection!") == 0, "Captured output should match expected output");
} // end case

FOSSIL_TEST(cpp_mock_io_compare_output_macro) {
    // Captured and expected outputs
    const char *captured = "Macro comparison test!";
    const char *expected = "Macro comparison test!";

    // Use the macro to compare outputs
    bool result = FOSSIL_MOCK_COMPARE_OUTPUT(captured, expected);

    // Test cases
    FOSSIL_TEST_ASSUME(result == true, "Captured output should match expected output using macro");
} // end case

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_mock_test_cases) {
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_initialization);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_addition);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_destruction);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_function_creation);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_alias_creation);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_struct_creation);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_type_handling);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_edge_cases);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_call_list_large_arguments);

    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_macro_initialization);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_macro_addition);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_macro_destruction);

    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_io_capture_output);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_io_compare_output);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_io_redirect_stdout_macro);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_io_compare_output_macro);
    FOSSIL_TEST_ADD(cpp_mock_suite, cpp_mock_io_compare_output);

    FOSSIL_TEST_REGISTER(cpp_mock_suite);
} // end of group
