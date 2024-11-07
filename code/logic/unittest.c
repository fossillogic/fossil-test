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
fossil_options_t global_options;
jmp_buf env;

// Global list to store all test suites
test_suite_t *global_test_suites = NULL;

char *_custom_fossil_test_strdup(const char *str) {
    size_t len = strlen(str) + 1;
    char *new_str = (char *)malloc(len);
    if (new_str == NULL) {
        return NULL;
    }
    memcpy(new_str, str, len);
    return new_str;
}

// Initialize the options structure
fossil_options_t init_options(void) {
    fossil_options_t options;
    options.show_version = false;
    options.show_help = false;
    options.show_tip = false;
    options.show_info = false;
    options.show_author = false;
    options.only_tags = false;
    options.reverse = false;
    options.repeat_enabled = false;
    options.repeat_count = 1;
    options.shuffle_enabled = false;
    options.verbose_enabled = false;
    options.verbose_level = 1;
    options.list_tests = false;
    options.summary_enabled = false;
    options.color_enabled = false;
    options.sanity_enabled = false;
    return options;
}

// Parse command-line arguments
fossil_options_t fossil_options_parse(int argc, char **argv) {
    fossil_options_t options = init_options();
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0) {
            options.show_version = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            options.show_help = true;
        } else if (strcmp(argv[i], "--tip") == 0) {
            options.show_tip = true;
        } else if (strcmp(argv[i], "--info") == 0) {
            options.show_info = true;
        } else if (strcmp(argv[i], "--author") == 0) {
            options.show_author = true;
        } else if (strcmp(argv[i], "only") == 0) {
            options.only_tags = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                strcpy(options.only_tags_value, argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "reverse") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.reverse = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.reverse = false;
            }
        } else if (strcmp(argv[i], "repeat") == 0) {
            options.repeat_enabled = true;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options.repeat_count = atoi(argv[i + 1]);
                i++;
            }
        } else if (strcmp(argv[i], "shuffle") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.shuffle_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.shuffle_enabled = false;
            }
        } else if (strcmp(argv[i], "verbose") == 0) {
            options.verbose_enabled = true;
            if (i + 1 < argc && strcmp(argv[i + 1], "cutback") == 0) {
                options.verbose_level = 0;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "verbose") == 0) {
                options.verbose_level = 2;
            }
        } else if (strcmp(argv[i], "list") == 0) {
            options.list_tests = true;
        } else if (strcmp(argv[i], "summary") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.summary_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.summary_enabled = false;
            }
        } else if (strcmp(argv[i], "color") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.color_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.color_enabled = false;
            }
        } else if (strcmp(argv[i], "sanity") == 0) {
            if (i + 1 < argc && strcmp(argv[i + 1], "enable") == 0) {
                options.sanity_enabled = true;
            } else if (i + 1 < argc && strcmp(argv[i + 1], "disable") == 0) {
                options.sanity_enabled = false;
            }
        }
    }
    
    return options;
}

// Initialize the test framework
void fossil_test_init(int argc, char **argv) {
    fossil_options_parse(argc, argv);

    pass_count = 0;
    fail_count = 0;
    skip_count = 0;
    unexpected_count = 0;
}

// Cleanup after test execution
void fossil_test_cleanup(void) {
    while (global_test_suites != NULL) {
        test_suite_t *current_suite = global_test_suites;
        global_test_suites = global_test_suites->next;

        // Free all test cases in the suite
        while (current_suite->tests->front != NULL) {
            fossil_test_remove_front(current_suite->tests);  // this already frees each test case
        }

        free(current_suite->tests);
        free(current_suite);
    }
}

void fossil_test_summary(void) {
    printf("Test Summary:\n");
    printf("  Passed: %d\n", pass_count);
    printf("  Failed: %d\n", fail_count);
    printf("  Skipped: %d\n", skip_count);
    printf("  Unexpected: %d\n", unexpected_count);
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

    // Free the stack_trace frames for the test case
    stack_frame_t *frame = test_to_remove->stack_trace;
    while (frame != NULL) {
        stack_frame_t *next = frame->next;
        free(frame);
        frame = next;
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
        if (frame) {  // Ensure allocation succeeded
            frame->func = func;
            frame->file = file;
            frame->line = line;
            frame->next = current_test->stack_trace;
            current_test->stack_trace = frame;
        }

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
