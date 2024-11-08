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
#ifndef FOSSIL_TEST_CORE_H
#define FOSSIL_TEST_CORE_H

#define MAX_NAME_LENGTH 256

// Color codes
#define COLOR_RESET      "\033[0m"
#define COLOR_PASS       "\033[32m"  // Green
#define COLOR_FAIL       "\033[31m"  // Red
#define COLOR_SKIP       "\033[33m"  // Yellow
#define COLOR_INFO       "\033[34m"  // Blue
#define COLOR_BDD       "\033[35m"  // Magenta
#define COLOR_CYAN      "\033[36m"  // Cyan

#include <setjmp.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define the structure to hold parsed options
typedef struct {
    bool show_version;
    bool show_help;
    bool show_info;
    bool reverse;
    bool repeat_enabled;
    int repeat_count;
    bool shuffle_enabled;
} fossil_options_t;

typedef enum {
    TEST_STATUS_PASS,
    TEST_STATUS_FAIL,
    TEST_STATUS_SKIP
} test_status_t;

// Stack frame structure for tracking function call details during failures
typedef struct stack_frame {
    const char *func;
    const char *file;
    int line;
    struct stack_frame *next;
} stack_frame_t;

// Test case structure
typedef struct test_case {
    const char *name;                    // Test case name
    void (*test_func)(void);             // Pointer to test function
    void (*setup_func)(void);            // Pointer to setup function (optional)
    void (*teardown_func)(void);         // Pointer to teardown function (optional)
    test_status_t status;                // Test status (pass, fail, skip)
    const char *failure_message;         // Failure message (if any)
    stack_frame_t *stack_trace;          // Stack trace for failures
    double execution_time;               // Execution time of the test
    struct test_case *next;              // Pointer to next test case in the list
} test_case_t;

// Test suite structure
typedef struct test_suite {
    const char *name;                    // Suite name
    void (*suite_setup_func)(void);      // Suite setup function (optional)
    void (*suite_teardown_func)(void);   // Suite teardown function (optional)
    double total_execution_time;         // Total execution time of all test cases
    test_case_t *tests;                  // List of test cases
    struct test_suite *next;             // Pointer to next suite in the list
} test_suite_t;

typedef struct fossil_test_env {
    fossil_options_t options;
    jmp_buf env;
    int total_tests;
    int pass_count;
    int fail_count;
    int skip_count;
    int unexpected_count;
    double total_execution_time;
    test_suite_t *test_suites;
} fossil_test_env_t;

// *****************************************************************************
// Function declarations
// *****************************************************************************

/**
 * @brief Creates a new test suite.
 * 
 * @param name The name of the test suite.
 * @return A pointer to the created test suite.
 */
test_suite_t* fossil_test_create_suite(const char *name);

/**
 * @brief Registers a test suite with the test environment.
 * 
 * @param env The test environment.
 * @param suite The test suite to register.
 */
void fossil_test_register_suite(fossil_test_env_t *env, test_suite_t *suite);

/**
 * @brief Adds a test case to a test suite.
 * 
 * @param suite The test suite.
 * @param test_case The test case to add.
 */
void fossil_test_add_case(test_suite_t *suite, test_case_t *test_case);

/**
 * @brief Removes a test case from a test suite.
 * 
 * @param suite The test suite.
 * @param test_case The test case to remove.
 */
void fossil_test_remove_case(test_suite_t *suite, test_case_t *test_case);

/**
 * @brief Sets up a test case.
 * 
 * @param test_case The test case to set up.
 */
void fossil_test_case_setup(test_case_t *test_case);

/**
 * @brief Tears down a test case.
 * 
 * @param test_case The test case to tear down.
 */
void fossil_test_case_teardown(test_case_t *test_case);

/**
 * @brief Runs a test case.
 * 
 * @param test_case The test case to run.
 * @param env The test environment.
 */
void fossil_test_run_case(test_case_t *test_case, fossil_test_env_t *env);

/**
 * @brief Runs all test cases in a test suite.
 * 
 * @param suite The test suite to run.
 * @param env The test environment.
 */
void fossil_test_run_suite(test_suite_t *suite, fossil_test_env_t *env);

/**
 * @brief Asserts a condition and prints a message if the assertion fails.
 * 
 * @param condition The condition to assert.
 * @param message The message to print if the assertion fails.
 * @param file The file where the assertion failed.
 * @param line The line number where the assertion failed.
 * @param func The function where the assertion failed.
 */
void fossil_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func);

/**
 * @brief Initializes the test environment.
 * 
 * @param env The test environment to initialize.
 */
void fossil_test_init(fossil_test_env_t *env, int argc, char **argv);

/**
 * @brief Prints a summary of the test results.
 * 
 * @param env The test environment.
 */
void fossil_test_summary(fossil_test_env_t *env);

/**
 * @brief Runs all test suites and test cases in the test environment.
 * 
 * @param env The test environment.
 */
void fossil_test_run_all(fossil_test_env_t *env);

/**
 * @brief Prints the stack trace.
 * 
 * @param stack_trace The stack trace to print.
 */
void fossil_test_print_stack_trace(stack_frame_t *stack_trace);

// *****************************************************************************
// Macro definitions
// *****************************************************************************

// Assertion macro to assume a condition is true
#define _FOSSIL_TEST_ASSUME(condition, message) \
    fossil_test_assert_internal((condition), (message), __FILE__, __LINE__, __func__)

// Macro for defining a test case
#define _FOSSIL_TEST_CASE(test_name) \
    void test_name##_test_func(void); \
    test_case_t test_name##_test_case = { \
        .name = #test_name, \
        .test_func = test_name##_test_func, \
        .setup_func = NULL, \
        .teardown_func = NULL, \
        .status = TEST_STATUS_PASS, \
        .failure_message = NULL, \
        .stack_trace = NULL, \
        .execution_time = 0.0, \
        .next = NULL \
    }; \
    void test_name##_test_func(void)

// Macro for defining test data structures
#define _FOSSIL_TEST_DATA(name) \
    typedef struct name

// Macro for setting up a test case
#define _FOSSIL_TEST_SETUP(name) \
    void name##_setup_func(void)

// Macro for tearing down a test case
#define _FOSSIL_TEST_TEARDOWN(name) \
    void name##_teardown_func(void)

// Macro to create a test suite with setup and teardown hooks
#define _FOSSIL_TEST_SUITE(suite_name) \
    void suite_name##_setup_func(void); \
    void suite_name##_teardown_func(void); \
    test_suite_t suite_name = { \
        .name = #suite_name, \
        .suite_setup_func = suite_name##_setup_func, \
        .suite_teardown_func = suite_name##_teardown_func, \
        .total_execution_time = 0.0, \
        .tests = NULL, \
        .next = NULL \
    }

// Macro to register a suite with the test environment
#define _FOSSIL_TEST_REGISTER(suite) \
    fossil_test_register_suite(_env, &suite)

// Macro to add a test case to a suite
#define _FOSSIL_TEST_ADD(suite, test) \
    fossil_test_add_case(&suite, &(test##_test_case))

// Macro to define a test group, grouping tests under a common environment
#define _FOSSIL_TEST_GROUP(name) \
    void name##_test_group(fossil_test_env_t *_env)

// Macro to export a test group
#define _FOSSIL_TEST_EXPORT(name) \
    void name##_test_group(fossil_test_env_t *_env)

// Macro to import a test group into the environment
#define _FOSSIL_TEST_IMPORT(name) \
    name##_test_group(&_env)

// Main runner management macros

// Macro to initialize the test environment and handle command-line args
#define _FOSSIL_TEST_START(argc, argv) \
    fossil_test_env_t _env; \
    fossil_test_init(&_env, argc, argv)

// Macro to run all tests in the environment
#define _FOSSIL_TEST_RUN() \
    fossil_test_run_all(&_env)

// Macro to output a summary of the test results
#define _FOSSIL_TEST_SUMMARY() \
    fossil_test_summary(&_env)

// Macro to clean up after all tests and exit with appropriate status code
#define _FOSSIL_TEST_END()  \
    int fail_count = _env.fail_count; \
    return fail_count > 0 ? EXIT_FAILURE : EXIT_SUCCESS

// Behavior-driven development macros for Given, When, Then structure

#define _GIVEN(description) \
    if (0) { \
        printf(COLOR_BDD "Given %s\n" COLOR_RESET, description); \
    }

#define _WHEN(description) \
    if (0) { \
        printf(COLOR_BDD "When %s\n" COLOR_RESET, description); \
    }

#define _THEN(description) \
    if (0) { \
        printf(COLOR_BDD "Then %s\n" COLOR_RESET, description); \
    }

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <iostream>
#include <string>

namespace fossil {

}
#endif

#endif
