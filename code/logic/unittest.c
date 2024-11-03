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
#include "fossil/test/unittest.h"

// Global variables for tracking test results
int pass_count = 0;
int fail_count = 0;
int skip_count = 0;
int unexpected_count = 0;
jmp_buf env;

// Global list to store all test suites
test_suite_t *global_test_suites = NULL;

// Initialize the test framework
void fossil_test_init(void) {
    pass_count = 0;
    fail_count = 0;
    skip_count = 0;
    unexpected_count = 0;
}

// Cleanup after test execution
void fossil_test_cleanup(void) {
    // Cleanup for all test suites can be added here
}

void fossil_test_summary(void) {
    printf("Test Summary:\n");
    printf("  Passed: %d\n", pass_count);
    printf("  Failed: %d\n", fail_count);
    printf("  Skipped: %d\n", skip_count);
    printf("  Unexpected: %d\n", unexpected_count);
}

// Register a test suite by adding it to the global list
void fossil_test_register_suite(test_suite_t *suite) {
    if (global_test_suites == NULL) {
        global_test_suites = suite;
    } else {
        test_suite_t *current = global_test_suites;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = suite;
    }
}

// Add a test case to the double-ended priority queue
void fossil_test_add_case(double_ended_priority_queue_t *queue, test_case_t *test) {
    if (queue->back == NULL) {
        queue->front = queue->back = test;
        test->next = test->prev = NULL;
    } else {
        queue->back->next = test;
        test->prev = queue->back;
        test->next = NULL;
        queue->back = test;
    }
}

// Remove a test case from the front of the queue
void fossil_test_remove_front(double_ended_priority_queue_t *queue) {
    if (queue->front == NULL) return;

    test_case_t *test_to_remove = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->back = NULL;
    } else {
        queue->front->prev = NULL;
    }

    free(test_to_remove);
}

// Remove a test case from the back of the queue
void fossil_test_remove_back(double_ended_priority_queue_t *queue) {
    if (queue->back == NULL) return;

    test_case_t *test_to_remove = queue->back;
    queue->back = queue->back->prev;

    if (queue->back == NULL) {
        queue->front = NULL;
    } else {
        queue->back->next = NULL;
    }

    free(test_to_remove);
}

// Run all tests in the test suite
void fossil_test_run_suite(test_suite_t *suite) {
    printf("Running tests in suite: %s\n", suite->name);
    clock_t suite_start_time = clock();

    if (suite->suite_setup_func) {
        suite->suite_setup_func();
    }

    while (suite->tests->front != NULL) {
        test_case_t *test = suite->tests->front;
        test->status = test_status_pass;

        if (test->setup_func) {
            test->setup_func();
        }

        clock_t test_start_time = clock();

        if (setjmp(env) == 0) {
            test->test_func();
        } else {
            test->status = test_status_fail;
            unexpected_count++;
            printf("FAIL: %s - %s\n", test->name, test->failure_message);

            printf("Stack Trace:\n");
            stack_frame_t *current_frame = test->stack_trace;
            while (current_frame != NULL) {
                printf("  at %s (%s:%d)\n", current_frame->func, current_frame->file, current_frame->line);
                current_frame = current_frame->next;
            }
        }

        test->execution_time = (double)(clock() - test_start_time) / CLOCKS_PER_SEC;

        if (test->teardown_func) {
            test->teardown_func();
        }

        if (test->status == test_status_pass) {
            printf("PASS: %s (%.3f seconds)\n", test->name, test->execution_time);
            pass_count++;
        } else if (test->status == test_status_fail) {
            fail_count++;
        } else if (test->status == test_status_skip) {
            printf("SKIP: %s\n", test->name);
            skip_count++;
        }

        stack_frame_t *frame_to_free;
        while (test->stack_trace != NULL) {
            frame_to_free = test->stack_trace;
            test->stack_trace = test->stack_trace->next;
            free(frame_to_free);
        }

        fossil_test_remove_front(suite->tests);
    }

    if (suite->suite_teardown_func) {
        suite->suite_teardown_func();
    }

    suite->total_execution_time = (double)(clock() - suite_start_time) / CLOCKS_PER_SEC;
    printf("Total time for suite %s: %.3f seconds\n", suite->name, suite->total_execution_time);
}

/**
 * Assert a condition in a test case.
 *
 * @param condition The condition to assert.
 * @param message The failure message if the condition is false.
 * @param file The file where the assertion failed.
 * @param line The line number where the assertion failed.
 * @param func The function where the assertion failed.
 */
void fossil_test_assume(bool condition, const char *message, const char *file, int line, const char *func) {
    if (!condition) {
        test_case_t *current_test = global_test_suites->tests->back;
        current_test->status = test_status_fail;
        current_test->failure_message = message;

        stack_frame_t *frame = malloc(sizeof(stack_frame_t));
        frame->func = func;
        frame->file = file;
        frame->line = line;
        frame->next = current_test->stack_trace;
        current_test->stack_trace = frame;

        longjmp(env, 1);
    }
}

void fossil_test_register_suite(test_suite_t *suite) {
    if (!suite) return; // Ensure the suite is not NULL

    // Link the new suite at the front of the global list
    suite->next = global_test_suites;
    global_test_suites = suite;

    printf("Registered test suite: %s\n", suite->name);
}

void fossil_test_assume(bool condition, const char *message, const char *file, int line, const char *func) {
    if (!condition) {
        fprintf(stderr, "ASSUMPTION FAILED: %s\nFile: %s, Line: %d, Function: %s\n", message, file, line, func);
        // Increment the unexpected count for reporting
        unexpected_count++;
    }
}
