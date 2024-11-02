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

// *****************************************************************************
// Constants
// *****************************************************************************

// ANSI color codes for output
#define FOSSIL_TEST_COLOR_RESET   "\033[0m"
#define FOSSIL_TEST_COLOR_GREEN   "\033[32m"
#define FOSSIL_TEST_COLOR_RED     "\033[31m"
#define FOSSIL_TEST_COLOR_YELLOW  "\033[33m"
#define FOSSIL_TEST_COLOR_BLUE    "\033[34m"

// *****************************************************************************
// Type definitions
// *****************************************************************************

typedef enum {
    FOSSIL_TEST_PASS,
    FOSSIL_TEST_FAIL,
    FOSSIL_TEST_SKIP,
    FOSSIL_TEST_UNEXPECTED
} fossil_test_result_t;

typedef enum {
    FOSSIL_COLOR_DEFAULT,
    FOSSIL_COLOR_GREEN,
    FOSSIL_COLOR_RED,
    FOSSIL_COLOR_YELLOW,
    FOSSIL_COLOR_BLUE
} fossil_test_color_t;

typedef struct fossil_test_case {
    const char *name;
    void (*test_func)(void);
    fossil_test_result_t result;
    struct fossil_test_case *next;
} fossil_test_case_t;

typedef struct fossil_test_log {
    const char *message;
    fossil_test_result_t result;
    struct fossil_test_log *prev;
    struct fossil_test_log *next;
} fossil_test_log_t;

typedef struct fossil_test_suite {
    const char *name;
    fossil_test_case_t *test_head;
    struct fossil_test_suite *next;
} fossil_test_suite_t;

typedef struct {
    fossil_test_suite_t *suite_head;
    fossil_test_log_t *log_head;
    int pass_count;
    int fail_count;
    int skip_count;
    int unexpected_count;
    jmp_buf jump_env;
} fossil_test_runner_t;

// *****************************************************************************
// Function prototypes
// *****************************************************************************

/**
 * @brief Create a new test runner.
 * 
 * @return A pointer to the newly created test runner.
 */
fossil_test_runner_t *fossil_test_create_runner(void);

/**
 * @brief Add a test case to a test suite.
 * 
 * @param suite The test suite to which the test case will be added.
 * @param name The name of the test case.
 * @param test_func The function that implements the test case.
 */
void fossil_test_add_case(fossil_test_suite_t *suite, const char *name, void (*test_func)(void));

/**
 * @brief Create a new test suite.
 * 
 * @param runner The test runner that will manage the test suite.
 * @param name The name of the test suite.
 * @return A pointer to the newly created test suite.
 */
fossil_test_suite_t *fossil_test_create_suite(fossil_test_runner_t *runner, const char *name);

/**
 * @brief Log a message with a specific test result.
 * 
 * @param runner The test runner that manages the log.
 * @param message The message to log.
 * @param result The result of the test case.
 */
void fossil_test_log(fossil_test_runner_t *runner, const char *message, fossil_test_result_t result);

/**
 * @brief Run all test cases in a test suite.
 * 
 * @param runner The test runner that manages the test suite.
 * @param suite The test suite to run.
 */
void fossil_test_run_suite(fossil_test_runner_t *runner, fossil_test_suite_t *suite);

/**
 * @brief Run all test suites managed by the test runner.
 * 
 * @param runner The test runner that manages the test suites.
 */
void fossil_test_run(fossil_test_runner_t *runner);

/**
 * @brief Generate a report of the test results.
 * 
 * @param runner The test runner that manages the test results.
 */
void fossil_test_report(fossil_test_runner_t *runner);

/**
 * @brief Free the memory allocated for the test runner.
 * 
 * @param runner The test runner to free.
 */
void fossil_test_free_runner(fossil_test_runner_t *runner);

/**
 * @brief Print text in a specified color.
 * 
 * @param text The text to print.
 * @param color The color to use for printing the text.
 */
void fossil_test_print_color(const char *text, fossil_test_color_t color);

// *****************************************************************************
// Macros for defining and adding test cases
// *****************************************************************************

#define FOSSIL_TEST(name) void name(void)
#define FOSSIL_TEST_SUITE(name) \
    fossil_test_suite_t name = { \
        .name = #name, \
        .tests = NULL, \
        .test_count = 0 \
    }
#define FOSSIL_TEST_SETUP(name)    void name##_setup(void)
#define FOSSIL_TEST_TEARDOWN(name) void name##_teardown(void)

#define FOSSIL_TEST_GROUP(name)    void name##_group(fossil_test_runner_t runner)
#define FOSSIL_TEST_IMPORT(name)   void name##_group(fossil_test_runner_t runner)
#define FOSSIL_TEST_EXPORT(name)   void name##_group(fossil_test_runner_t runner)

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

#define FOSSIL_TEST_ADDF(queue, test_func, suite) \
    do { \
        fossil_test_case_t *test_case = malloc(sizeof(fossil_test_case_t)); \
        test_case->name = #test_func; \
        test_case->test_func = test_func; \
        test_case->result = FOSSIL_TEST_SKIP; \
        test_case->duration = 0.0; \
        test_case->is_expected_fail = false; \
        test_case->is_ignored = false; \
        fossil_test_add_suite(suite, test_case); \
    } while(0)

#define FOSSIL_TEST_ASSUME(runner, condition, message) \
    do { \
        if (!(condition)) { \
            fossil_test_log(runner, message, FOSSIL_TEST_FAIL); \
            runner->fail_count++; \
            longjmp(runner->jump_env, 1); \
        } else { \
            fossil_test_log(runner, message, FOSSIL_TEST_PASS); \
            runner->pass_count++; \
        } \
    } while (0)

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
