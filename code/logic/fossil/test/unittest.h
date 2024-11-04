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

// Test status enumeration
typedef enum {
    test_status_pass,
    test_status_fail,
    test_status_skip,
    test_status_unexpected
} test_status_t;

// Stack frame structure for stack traces
typedef struct stack_frame {
    const char *func;
    const char *file;
    int line;
    struct stack_frame *next;
} stack_frame_t;

// Test case structure
typedef struct test_case {
    const char *name;
    void (*test_func)(void);
    void (*setup_func)(void);
    void (*teardown_func)(void);
    const char *tags;
    test_status_t status;
    const char *failure_message;
    double execution_time;
    stack_frame_t *stack_trace;
    struct test_case *next;
    struct test_case *prev;
} test_case_t;

// Double-ended priority queue structure for test cases
typedef struct double_ended_priority_queue {
    test_case_t *front;
    test_case_t *back;
} double_ended_priority_queue_t;

// Test suite structure with setup and teardown hooks
typedef struct test_suite {
    const char *name;
    double_ended_priority_queue_t *tests;
    double total_execution_time;
    void (*suite_setup_func)(void);
    void (*suite_teardown_func)(void);
    struct test_suite *next; // Pointer to next suite in the global list
} test_suite_t;

// Global variables for test results
extern int pass_count;
extern int fail_count;
extern int skip_count;
extern int unexpected_count;
extern jmp_buf env;

// List to store all test suites
extern test_suite_t *global_test_suites;

// *****************************************************************************
// Function declarations
// *****************************************************************************

/**
 * Initialize the test framework.
 */
void fossil_test_init(void);

/**
 * Clean up the test framework.
 */
void fossil_test_cleanup(void);

/**
 * Print a summary of the test results.
 */
void fossil_test_summary(void);

/**
 * Add a test case to the double-ended priority queue.
 *
 * @param queue The double-ended priority queue.
 * @param test The test case to add.
 */
void fossil_test_add_case(double_ended_priority_queue_t *queue, test_case_t *test);

/**
 * Remove the front test case from the double-ended priority queue.
 *
 * @param queue The double-ended priority queue.
 */
void fossil_test_remove_front(double_ended_priority_queue_t *queue);

/**
 * Remove the back test case from the double-ended priority queue.
 *
 * @param queue The double-ended priority queue.
 */
void fossil_test_remove_back(double_ended_priority_queue_t *queue);

/**
 * Run all test cases in a test suite.
 *
 * @param suite The test suite to run.
 */
void fossil_test_run_suite(test_suite_t *suite);

/**
 * Assert a condition in a test case.
 *
 * @param condition The condition to assert.
 * @param message The failure message if the condition is false.
 * @param file The file where the assertion failed.
 * @param line The line number where the assertion failed.
 * @param func The function where the assertion failed.
 */
void fossil_test_assume(bool condition, const char *message, const char *file, int line, const char *func);

/**
 * Register a test suite with the test framework.
 *
 * @param suite The test suite to register.
 */
void fossil_test_register_suite(test_suite_t *suite);

// *****************************************************************************
// Macro definitions
// *****************************************************************************

#define _FOSSIL_TEST_ASSUME(condition, message) fossil_test_assume(condition, message, __FILE__, __LINE__, __func__)

// Macro for defining a test case
#define _FOSSIL_TEST_CASE(test_name) \
    void test_name##_test_func(void); \
    test_case_t test_name##_test_case = { \
        .name = #test_name, \
        .test_func = test_name##_test_func, \
        .setup_func = NULL, \
        .teardown_func = NULL, \
        .tags = NULL, \
        .status = test_status_pass, \
        .failure_message = NULL, \
        .execution_time = 0.0, \
        .stack_trace = NULL, \
        .next = NULL, \
        .prev = NULL \
    }; \
    void test_name##_test_func(void)

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
        .tests = NULL, \
        .total_execution_time = 0.0, \
        .suite_setup_func = suite_name##_setup_func, \
        .suite_teardown_func = suite_name##_teardown_func, \
        .next = NULL \
    }

// Macro to add a test case to a suite
#define _FOSSIL_TEST_ADD(suite, test) \
    fossil_test_add_case((suite).tests, &(test##_test_case));

#define _FOSSIL_TEST_GROUP(name) \
    void name##_test_group(void)

#define _FOSSIL_TEST_EXPORT(name) \
    void name##_test_group(void)

#define _FOSSIL_TEST_IMPORT(name) \
    name##_test_group()

// main runner managment

#define _FOSSIL_TEST_START() \
    fossil_test_init()

#define _FOSSIL_TEST_RUN() \
    { \
        test_suite_t *suites = global_test_suites; \
        while (suites != NULL) { \
            fossil_test_run_suite(suites); \
            suites = suites->next; \
        } \
    }

#define _FOSSIL_TEST_SUMMARY() \
    fossil_test_summary()

#define _FOSSIL_TEST_END()  \
    fossil_test_cleanup(); \
    return fail_count > 0 ? EXIT_FAILURE : EXIT_SUCCESS

#define _GIVEN(description) \
    if (1) { \
        printf("Given %s\n", description); \
    }

#define _WHEN(description) \
    if (1) { \
        printf("When %s\n", description); \
    }

#define _THEN(description) \
    if (1) { \
        printf("Then %s\n", description); \
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
