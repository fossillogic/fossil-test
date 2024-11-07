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

int pass_count;
int fail_count;
int skip_count;
int unexpected_count;

jmp_buf test_jump_buffer; // This will hold the jump buffer for longjmp

// Global variable to hold the current test case (set to the current test case).
test_case_t *current_test;

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
    options.reverse = false;
    options.repeat_enabled = false;
    options.repeat_count = 1;
    options.shuffle_enabled = false;
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
        }
    }
    
    return options;
}

// Creates and returns a new test suite
test_suite_t* fossil_test_create_suite(const char *name) {
    test_suite_t *suite = (test_suite_t*)malloc(sizeof(test_suite_t));
    suite->name = name;
    suite->suite_setup_func = NULL;
    suite->suite_teardown_func = NULL;
    suite->tests = NULL;
    suite->next = NULL;
    return suite;
}

// Registers a test suite in the environment
void fossil_test_register_suite(fossil_test_env_t *env, test_suite_t *suite) {
    if (!suite) return;
    suite->next = env->test_suites;
    env->test_suites = suite;
    printf(COLOR_INFO "Registered test suite: %s\n" COLOR_RESET, suite->name);
}

// Adds a test case to a suite
void fossil_test_add_case(test_suite_t *suite, test_case_t *test_case) {
    if (!suite || !test_case) return;

    test_case->next = suite->tests;
    suite->tests = test_case;
}

// Removes and frees a test case from a suite
void fossil_test_remove_case(test_suite_t *suite, test_case_t *test_case) {
    if (!suite || !test_case) return;

    test_case_t *prev = NULL;
    test_case_t *curr = suite->tests;

    while (curr) {
        if (curr == test_case) {
            if (prev) {
                prev->next = curr->next;
            } else {
                suite->tests = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

// Setup for individual test case
void fossil_test_case_setup(test_case_t *test_case) {
    if (test_case && test_case->setup_func) {
        test_case->setup_func();
    }
}

// Teardown for individual test case
void fossil_test_case_teardown(test_case_t *test_case) {
    if (test_case && test_case->teardown_func) {
        test_case->teardown_func();
    }
}

// Run an individual test case
void fossil_test_run_case(test_case_t *test_case, fossil_test_env_t *env) {
    if (!test_case) return;

    test_case->status = TEST_STATUS_PASS;

    // Run setup
    fossil_test_case_setup(test_case);

    clock_t test_start_time = clock();
    if (setjmp(env->env) == 0) {
        test_case->test_func();
    } else {
        test_case->status = TEST_STATUS_FAIL;
        printf(COLOR_FAIL "FAIL: " COLOR_INFO " %s\n", test_case->name);
        printf("Failure Message: %s\n" COLOR_RESET, test_case->failure_message);
    }
    test_case->execution_time = (double)(clock() - test_start_time) / CLOCKS_PER_SEC;

    // Run teardown
    fossil_test_case_teardown(test_case);

    // Log result
    if (test_case->status == TEST_STATUS_PASS) {
        printf(COLOR_PASS "PASS: " COLOR_INFO " %s (%.3f seconds)\n" COLOR_RESET, test_case->name, test_case->execution_time);
    } else if (test_case->status == TEST_STATUS_FAIL) {
        env->fail_count++;
    } else if (test_case->status == TEST_STATUS_SKIP) {
        env->skip_count++;
    }
}

// Run all test cases in a test suite
void fossil_test_run_suite(test_suite_t *suite, fossil_test_env_t *env) {
    if (!suite) return;

    printf(COLOR_INFO "Running suite: %s\n" COLOR_RESET, suite->name);
    if (suite->suite_setup_func) {
        suite->suite_setup_func();
    }

    double total_execution_time = 0.0;
    test_case_t *current_test = suite->tests;
    while (current_test) {
        fossil_test_run_case(current_test, env);
        total_execution_time += current_test->execution_time;
        current_test = current_test->next;
    }

    if (suite->suite_teardown_func) {
        suite->suite_teardown_func();
    }

    printf(COLOR_CYAN "Total execution time for suite %s: %.3f seconds\n" COLOR_RESET, suite->name, total_execution_time);
}

// Internal function to handle assertions
void fossil_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func) {
    if (!condition) {
        printf("Assertion failed: %s (%s:%d in %s)\n", message, file, line, func);
        longjmp(test_jump_buffer, 1); // Jump back to test case failure handler
    }
}

void fossil_test_run_all(fossil_test_env_t *env) {
    test_suite_t *current_suite = env->test_suites;

    while (current_suite) {
        fossil_test_run_suite(current_suite, env);
        current_suite = current_suite->next;
    }
}

void fossil_test_init(fossil_test_env_t *env, int argc, char **argv) {
    env->options = fossil_options_parse(argc, argv);
    env->pass_count = 0;
    env->fail_count = 0;
    env->skip_count = 0;
    env->total_tests = 0;
    env->total_execution_time = 0.0;
    env->unexpected_count = 0;
    env->test_suites = NULL;
}

// Summary function for test results
void fossil_test_summary(fossil_test_env_t *env) {
    int total_tests = 0;
    int passed = 0;
    int failed = 0;
    int skipped = 0;
    double total_time = 0.0;

    test_suite_t *suite = env->test_suites;
    while (suite != NULL) {
        test_case_t *test = suite->tests;
        while (test != NULL) {
            total_tests++;
            total_time += test->execution_time;

            if (test->status == TEST_STATUS_PASS) {
                passed++;
            } else if (test->status == TEST_STATUS_FAIL) {
                failed++;
                if (test->failure_message) {
                    printf("Test '%s' failed: %s\n", test->name, test->failure_message);
                }
            } else if (test->status == TEST_STATUS_SKIP) {
                skipped++;
            }

            test = test->next;
        }
        suite = suite->next;
    }

    printf(COLOR_INFO "====================================" COLOR_RESET);
    printf(COLOR_INFO "\nFossil Test Summary:\n" COLOR_RESET);
    printf(COLOR_INFO "====================================\n" COLOR_RESET);

    printf(COLOR_PASS "Passed: %d\n" COLOR_RESET, passed);
    printf(COLOR_FAIL "Failed: %d\n" COLOR_RESET, failed);
    printf(COLOR_SKIP "Skipped: %d\n" COLOR_RESET, skipped);
    printf(COLOR_INFO "Total: %d tests\n" COLOR_RESET, passed + failed + skipped);

    // Optionally, you could add the total execution time summary here
    printf(COLOR_INFO "\n====================================\n" COLOR_RESET);
    printf(COLOR_INFO "Total execution time: %.3f seconds\n" COLOR_RESET, env->total_execution_time);
    printf(COLOR_INFO "====================================\n" COLOR_RESET);
    
    if (failed > 0) {
        printf("Some tests failed.\n");
    } else {
        printf("All tests passed.\n");
    }
}

void fossil_test_print_stack_trace(stack_frame_t *stack_trace) {
    stack_frame_t *current_frame = stack_trace;
    while (current_frame) {
        printf("  at %s (%s:%d)\n", current_frame->func, current_frame->file, current_frame->line);
        current_frame = current_frame->next;
    }
}
