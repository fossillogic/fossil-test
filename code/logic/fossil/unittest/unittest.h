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

// ANSI color codes for output
#define FOSSIL_TEST_COLOR_RESET   "\033[0m"
#define FOSSIL_TEST_COLOR_GREEN   "\033[32m"
#define FOSSIL_TEST_COLOR_RED     "\033[31m"
#define FOSSIL_TEST_COLOR_YELLOW  "\033[33m"
#define FOSSIL_TEST_COLOR_BLUE    "\033[34m"

// Enumeration for test result types
typedef enum {
    FOSSIL_TEST_PASS,
    FOSSIL_TEST_FAIL,
    FOSSIL_TEST_SKIP,
    FOSSIL_TEST_UNEXPECTED,
    FOSSIL_TEST_EXPECTED_FAIL, // New result type
    FOSSIL_TEST_IGNORED         // New result type
} fossil_test_result_t;

// Structure to store individual test case information
typedef struct fossil_test_case {
    const char *name;
    fossil_test_result_t result;
    void (*test_func)(void);
    double duration; // Duration for this test case
    bool is_expected_fail; // Flag for expected failures
    bool is_ignored; // Flag for ignored tests
} fossil_test_case_t;

// Structure for test suite
typedef struct fossil_test_suite {
    const char *name;
    fossil_test_case_t **tests;
    size_t test_count;
} fossil_test_suite_t;

// Priority Queue Node for Double-Ended Priority Queue
typedef struct fossil_test_node {
    fossil_test_case_t *test_case;
    struct fossil_test_node *next;
    struct fossil_test_node *prev;
} fossil_test_node_t;

// Double-Ended Priority Queue for Test Runner
typedef struct fossil_test_queue {
    fossil_test_node_t *head;
    fossil_test_node_t *tail;
    size_t count;
} fossil_test_queue_t;

// Stack for storing failure trace
typedef struct {
    const char *stack[256];
    int top;
} fossil_test_stack_t;

// Summary structure to track test results
typedef struct {
    size_t passed;
    size_t failed;
    size_t skipped;
    size_t unexpected;
    size_t expected_failed;
    size_t ignored;
} fossil_test_result_summary_t;

// Jump buffer for error handling
extern jmp_buf fossil_test_env; // Declare the jump buffer
extern fossil_test_stack_t fossil_test_stack; // Declare the stack for failure trace

/**
 * Initialize the test queue.
 *
 * @param queue Pointer to the test queue to initialize.
 */
void fossil_test_queue_init(fossil_test_queue_t *queue);

/**
 * Enqueue a test case into the test queue.
 *
 * @param queue Pointer to the test queue.
 * @param test_case Pointer to the test case to enqueue.
 */
void fossil_test_enqueue(fossil_test_queue_t *queue, fossil_test_case_t *test_case);

/**
 * Dequeue a test case from the test queue.
 *
 * @param queue Pointer to the test queue.
 * @return Pointer to the dequeued test case.
 */
fossil_test_case_t *fossil_test_dequeue(fossil_test_queue_t *queue);

/**
 * Free the memory allocated for the test queue.
 *
 * @param queue Pointer to the test queue to free.
 */
void fossil_test_queue_free(fossil_test_queue_t *queue);

/**
 * Push a trace message onto the failure stack.
 *
 * @param stack Pointer to the failure stack.
 * @param trace Trace message to push onto the stack.
 */
void fossil_test_stack_push(fossil_test_stack_t *stack, const char *trace);

/**
 * Print the contents of the failure stack.
 *
 * @param stack Pointer to the failure stack to print.
 */
void fossil_test_stack_print(const fossil_test_stack_t *stack);

/**
 * Handle a caught error by printing the error message and the failure stack.
 *
 * @param stack Pointer to the failure stack.
 * @param error_msg Error message to print.
 */
void fossil_test_catch(fossil_test_stack_t *stack, const char *error_msg);

/**
 * Run all test cases in the test queue.
 *
 * @param queue Pointer to the test queue.
 * @param stack Pointer to the failure stack.
 * @param summary Pointer to the summary structure to track test results.
 * @param verbose Flag to enable verbose output.
 */
void fossil_test_run(fossil_test_queue_t *queue, fossil_test_stack_t *stack, fossil_test_result_summary_t *summary, bool verbose);

/**
 * Print the summary of test results.
 *
 * @param summary Pointer to the summary structure containing test results.
 */
void fossil_test_summary(const fossil_test_result_summary_t *summary);

/**
 * Add a test case to a test suite.
 *
 * @param suite Pointer to the test suite.
 * @param test_case Pointer to the test case to add.
 */
void fossil_test_add_suite(fossil_test_suite_t *suite, fossil_test_case_t *test_case);

/**
 * Run all test cases in a test suite.
 *
 * @param suite Pointer to the test suite.
 * @param stack Pointer to the failure stack.
 * @param summary Pointer to the summary structure to track test results.
 * @param verbose Flag to enable verbose output.
 */
void fossil_test_run_suite(fossil_test_suite_t *suite, fossil_test_stack_t *stack, fossil_test_result_summary_t *summary, bool verbose);

/**
 * Set the setup function to be called before each test case.
 *
 * @param setup_func Pointer to the setup function.
 */
void fossil_test_setup(void (*setup_func)(void));

/**
 * Set the teardown function to be called after each test case.
 *
 * @param teardown_func Pointer to the teardown function.
 */
void fossil_test_teardown(void (*teardown_func)(void));

// Macros for defining and adding test cases
#define FOSSIL_TEST_DEFINE(name) void name(void)
#define FOSSIL_TEST_ADD(queue, test_func) \
    do { \
        fossil_test_case_t *test_case = malloc(sizeof(fossil_test_case_t)); \
        test_case->name = #test_func; \
        test_case->test_func = test_func; \
        test_case->result = FOSSIL_TEST_SKIP; \
        test_case->duration = 0.0; \
        test_case->is_expected_fail = false; \
        test_case->is_ignored = false; \
        fossil_test_enqueue(queue, test_case); \
    } while(0)

#define FOSSIL_TEST_EXPECT_FAIL(test_func) \
    do { \
        fossil_test_case_t *test_case = malloc(sizeof(fossil_test_case_t)); \
        test_case->name = #test_func; \
        test_case->test_func = test_func; \
        test_case->result = FOSSIL_TEST_EXPECTED_FAIL; \
        test_case->duration = 0.0; \
        test_case->is_expected_fail = true; \
        test_case->is_ignored = false; \
        fossil_test_enqueue(queue, test_case); \
    } while(0)

#define FOSSIL_TEST_IGNORE(test_func) \
    do { \
        fossil_test_case_t *test_case = malloc(sizeof(fossil_test_case_t)); \
        test_case->name = #test_func; \
        test_case->test_func = test_func; \
        test_case->result = FOSSIL_TEST_IGNORED; \
        test_case->duration = 0.0; \
        test_case->is_expected_fail = false; \
        test_case->is_ignored = true; \
        fossil_test_enqueue(queue, test_case); \
    } while(0)

// Assertion Macro
#define FOSSIL_TEST_ASSERT(cond, msg, line, func, file) \
    do { \
        if (!(cond)) { \
            char formatted_msg[256]; \
            snprintf(formatted_msg, sizeof(formatted_msg), "%s (at %s:%d in %s)", msg, file, line, func); \
            fossil_test_stack_push(fossil_test_stack, formatted_msg); \
            fossil_test_catch(fossil_test_stack, "Assertion failed"); \
        } \
    } while(0)

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
