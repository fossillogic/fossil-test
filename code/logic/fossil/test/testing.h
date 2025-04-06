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
#ifndef FOSSIL_TEST_INTERNAL_H
#define FOSSIL_TEST_INTERNAL_H

#include "internal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum test_status
 * @brief Enumeration to represent the status of a test.
 * 
 * This enumeration defines the possible status values for a test, including
 * pass, fail, skip, empty, and timeout.
 */
typedef enum {
    TEST_STATUS_PASS,
    TEST_STATUS_FAIL,
    TEST_STATUS_SKIP,
    TEST_STATUS_EMPTY,
    TEST_STATUS_TTIMEOUT
} fossil_test_status_t;

/**
 * @struct test_case
 * @brief Structure to hold a test case.
 * 
 * This structure contains fields to hold information about a test case, including
 * the name, test function, setup function, teardown function, status, failure message,
 * execution time, and a pointer to the next test case.
 * 
 * @var test_case::name
 * Test case name
 * 
 * @var test_case::test_func
 * Pointer to test function
 * 
 * @var test_case::setup_func
 * Pointer to setup function (optional)
 * 
 * @var test_case::teardown_func
 * Pointer to teardown function (optional)
 * 
 * @var test_case::status
 * Test status (pass, fail, skip)
 * 
 * @var test_case::failure_message
 * Failure message (if any)
 * 
 * @var test_case::execution_time
 * Execution time of the test
 * 
 * @var test_case::next
 * Pointer to next test case in the list
 */
typedef struct test_case {
    const char *name;                    
    void (*test_func)(void);             
    void (*setup_func)(void);            
    void (*teardown_func)(void);         
    fossil_test_status_t status;                
    const char *failure_message;         
    double execution_time;               
    struct test_case *next;              
} fossil_test_case_t;

/**
 * @struct fossil_test_suite_t
 * @brief Structure to hold a test suite.
 * 
 * This structure contains fields to hold information about a test suite, including
 * the name, suite setup function, suite teardown function, total execution time,
 * list of test cases, and a pointer to the next test suite.
 * 
 * @var fossil_test_suite_t::name
 * Suite name
 * 
 * @var fossil_test_suite_t::suite_setup_func
 * Pointer to suite setup function (optional)
 * 
 * @var fossil_test_suite_t::suite_teardown_func
 * Pointer to suite teardown function (optional)
 * 
 * @var fossil_test_suite_t::total_execution_time
 * Total execution time of all test cases
 * 
 * @var fossil_test_suite_t::tests
 * List of test cases
 * 
 * @var fossil_test_suite_t::next
 * Pointer to next suite in the list
 */
typedef struct fossil_test_suite_t {
    const char *name;
    void (*suite_setup_func)(void);
    void (*suite_teardown_func)(void);
    double total_execution_time;
    fossil_test_case_t *tests;
    struct fossil_test_suite_t *next;
} fossil_test_suite_t;

/**
 * @struct fossil_test_env
 * @brief Structure to hold the environment for fossil tests.
 * 
 * This structure contains various fields to manage and track the state of 
 * test execution, including options, counts of different test outcomes, 
 * execution times, and a list of test suites.
 * 
 * @var fossil_test_env::options
 * Configuration options for the fossil test environment.
 * 
 * @var fossil_test_env::env
 * Environment buffer for handling non-local jumps (e.g., setjmp/longjmp).
 * 
 * @var fossil_test_env::total_tests
 * Total number of tests to be executed.
 * 
 * @var fossil_test_env::pass_count
 * Count of tests that have passed.
 * 
 * @var fossil_test_env::fail_count
 * Count of tests that have failed.
 * 
 * @var fossil_test_env::skip_count
 * Count of tests that have been skipped.
 * 
 * @var fossil_test_env::empty_count
 * Count of tests that are empty (i.e., no test cases).
 * 
 * @var fossil_test_env::timeout_count
 * Count of tests that have timed out.
 * 
 * @var fossil_test_env::unexpected_count
 * Count of tests that have encountered unexpected errors.
 * 
 * @var fossil_test_env::start_execution_time
 * Timestamp marking the start of test execution.
 * 
 * @var fossil_test_env::end_execution_time
 * Timestamp marking the end of test execution.
 * 
 * @var fossil_test_env::test_suites
 * Pointer to the list of test suites to be executed.
 */
typedef struct fossil_test_env {
    fossil_test_options_t options;
    jmp_buf env;
    int32_t total_tests;
    int32_t pass_count;
    int32_t fail_count;
    int32_t skip_count;
    int32_t empty_count;
    int32_t timeout_count;
    int32_t unexpected_count;
    double start_execution_time;
    double end_execution_time;
    fossil_test_suite_t *test_suites;
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
fossil_test_suite_t* fossil_test_create_suite(const char *name);

/**
 * @brief Registers a test suite with the test environment.
 * 
 * @param env The test environment.
 * @param suite The test suite to register.
 */
void fossil_test_register_suite(fossil_test_env_t *env, fossil_test_suite_t *suite);

/**
 * @brief Adds a test case to a test suite.
 * 
 * @param suite The test suite.
 * @param test_case The test case to add.
 */
void fossil_test_add_case(fossil_test_suite_t *suite, fossil_test_case_t *test_case);

/**
 * @brief Removes a test case from a test suite.
 * 
 * @param suite The test suite.
 * @param test_case The test case to remove.
 */
void fossil_test_remove_case(fossil_test_suite_t *suite, fossil_test_case_t *test_case);

/**
 * @brief Sets up a test case.
 * 
 * @param test_case The test case to set up.
 */
void fossil_test_case_setup(fossil_test_case_t *test_case);

/**
 * @brief Tears down a test case.
 * 
 * @param test_case The test case to tear down.
 */
void fossil_fossil_test_case_teardown(fossil_test_case_t *test_case);

/**
 * @brief Runs a test case.
 * 
 * @param test_case The test case to run.
 * @param env The test environment.
 */
void fossil_test_run_case(fossil_test_case_t *test_case, fossil_test_env_t *env);

/**
 * @brief Runs all test cases in a test suite.
 * 
 * @param suite The test suite to run.
 * @param env The test environment.
 */
void fossil_test_run_suite(fossil_test_suite_t *suite, fossil_test_env_t *env);

/**
 * @brief Internal function to handle assertions with anomaly detection.
 * 
 * This function is used internally by the test framework to handle assertions
 * and detect duplicate assertions. It is not intended to be called directly.
 * 
 * @param condition The condition to check.
 * @param message The message to display if the condition is false.
 * @param file The file name where the assertion occurred.
 * @param line The line number where the assertion occurred.
 * @param func The function name where the assertion occurred.
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

// *****************************************************************************
// Macro definitions
// *****************************************************************************

/**
 * @brief Macro to assume a condition in a test runner.
 * This macro is used to assert that a specific condition is true within a test
 * runner. If the condition is false, the test runner will output the specified
 * message and may abort the execution of the test case or test suite.
 */
#define _FOSSIL_TEST_ASSUME(condition, message) \
    fossil_test_assert_internal((condition), (message), __FILE__, __LINE__, __func__)

/**
 * @brief Macro to fail a test case.
 * 
 * This macro is used to fail a test case with a specific message. The test case
 * will be marked as failed, and the message will be displayed in the test results.
 */
#define _FOSSIL_TEST_SKIP(test_name, message) \
    test_name##_test_case.status = TEST_STATUS_SKIP; \
    test_name##_test_case.failure_message = message; \
    printf(FOSSIL_TEST_COLOR_YELLOW "SKIPPED: %s - %s\n" FOSSIL_TEST_COLOR_RESET, #test_name, message); \

/**
 * @brief Macro to define a test case.
 * 
 * This macro is used to define a test case, which is a single unit of testing
 * that verifies the correctness of a specific functionality. The test case
 * should contain the logic to set up the environment, execute the functionality,
 * and verify the results.
 * 
 * @param test_name The name of the test case.
 */
#ifdef __cplusplus
#define _FOSSIL_TEST_CASE(test_name) \
    void test_name##_test_func(void); \
    fossil_test_case_t test_name##_test_case = { \
        #test_name, \
        test_name##_test_func, \
        nullptr, \
        nullptr, \
        TEST_STATUS_PASS, \
        nullptr, \
        0.0, \
        nullptr \
    }; \
    void test_name##_test_func(void)
#else
#define _FOSSIL_TEST_CASE(test_name) \
    void test_name##_test_func(void); \
    fossil_test_case_t test_name##_test_case = { \
        .name = #test_name, \
        .test_func = test_name##_test_func, \
        .setup_func = NULL, \
        .teardown_func = NULL, \
        .status = TEST_STATUS_PASS, \
        .failure_message = NULL, \
        .execution_time = 0.0, \
        .next = NULL \
    }; \
    void test_name##_test_func(void)
#endif

/**
 * @brief Macro to define a test suite.
 * 
 * This macro is used to define a test suite, which is a collection of test cases
 * that are related to each other. The test suite can be executed as a whole to
 * verify the correctness of a group of functionalities.
 * 
 * @param suite_name The name of the test suite.
 */
#ifdef __cplusplus
#define _FOSSIL_TEST_SUITE(suite_name) \
    void suite_name##_setup_func(void); \
    void suite_name##_teardown_func(void); \
    fossil_test_suite_t suite_name = { \
        #suite_name, \
        suite_name##_setup_func, \
        suite_name##_teardown_func, \
        0.0, \
        nullptr, \
        nullptr \
    }
#else
#define _FOSSIL_TEST_SUITE(suite_name) \
    void suite_name##_setup_func(void); \
    void suite_name##_teardown_func(void); \
    fossil_test_suite_t suite_name = { \
        .name = #suite_name, \
        .suite_setup_func = suite_name##_setup_func, \
        .suite_teardown_func = suite_name##_teardown_func, \
        .total_execution_time = 0.0, \
        .tests = NULL, \
        .next = NULL \
    }
#endif

/**
 * @brief Macro to define a setup function for a test.
 * 
 * This macro is used to declare a setup function that will be executed before
 * each test case in a test suite. The setup function should contain the logic
 * to initialize the environment or state required for the test cases.
 * 
 * @param name The name of the setup function.
 */
#define _FOSSIL_TEST_SETUP(name) \
    void name##_setup_func(void)

/**
 * @brief Macro to define a teardown function for a test.
 * 
 * This macro is used to declare a teardown function that will be executed after
 * each test case in a test suite. The teardown function should contain the logic
 * to clean up the environment or state after the test cases have been executed.
 * 
 * @param name The name of the teardown function.
 */
#define _FOSSIL_TEST_TEARDOWN(name) \
    void name##_teardown_func(void)

/**
 * @brief Macro to register a test suite with the test framework.
 * 
 * This macro is used to register a test suite with the test framework. The test
 * suite will be added to the list of test suites that will be executed by the
 * test runner.
 * 
 * @param suite The test suite to register.
 */
#define _FOSSIL_TEST_REGISTER(suite) \
    fossil_test_register_suite(_env, &suite)

/**
 * @brief Macro to add a test case to a test suite.
 * 
 * This macro is used to add a test case to a test suite. The test case will be
 * executed when the test suite is run.
 * 
 * @param suite The test suite to add the test case to.
 * @param test The test case to add.
 */
#define _FOSSIL_TEST_ADD(suite, test) \
    fossil_test_add_case(&suite, &(test##_test_case))

/**
 * @brief Macro to define a test group.
 * 
 * This macro is used to define a test group, which is a collection of test cases
 * that are related to each other. The test group can be executed as a whole to
 * verify the correctness of a group of functionalities.
 * 
 * @param name The name of the test group.
 */
#ifdef __cplusplus
#define _FOSSIL_TEST_GROUP(name) \
    extern "C" void name##_test_group(fossil_test_env_t *_env)
#else
#define _FOSSIL_TEST_GROUP(name) \
    void name##_test_group(fossil_test_env_t *_env)
#endif

/**
 * @brief Macro to export a test group.
 * 
 * This macro is used to export a test group from a test file. The test group
 * will be available to other test files that import it.
 * 
 * @param name The name of the test group to export.
 */
#define _FOSSIL_TEST_EXPORT(name) \
    void name##_test_group(fossil_test_env_t *_env)

/**
 * @brief Macro to import a test group.
 * 
 * This macro is used to import a test group into the test runner. The test group
 * will be executed when the test runner is run.
 * 
 * @param name The name of the test group to import.
 */
#define _FOSSIL_TEST_IMPORT(name) \
    name##_test_group(&_env)

// Main runner management macros

/**
 * @brief Macro to start the test runner.
 * 
 * This macro is used to start the test runner, which will initialize the test
 * environment and set up the necessary structures for running the test cases.
 */
#define _FOSSIL_TEST_START(argc, argv) \
    fossil_test_env_t _env; \
    fossil_test_init(&_env, argc, argv)

/**
 * @brief Macro to run all test cases in the test suite.
 * 
 * This macro is used to run all test cases in the test suite. The test cases
 * will be executed in the order they were added to the suite.
 */
#define _FOSSIL_TEST_RUN() \
    fossil_test_run_all(&_env)

/**
 * @brief Macro to print the test summary.
 * 
 * This macro is used to print the test summary, which includes the number of
 * tests that passed, failed, and were skipped.
 */
#define _FOSSIL_TEST_SUMMARY() \
    fossil_test_summary(&_env)

/**
 * @brief Macro to end the test runner.
 * 
 * This macro is used to end the test runner, which will clean up the test
 * framework and return the appropriate exit code based on the test results.
 */
#define _FOSSIL_TEST_END()  \
    int fail_count = _env.fail_count; \
    return fail_count > 0 ? EXIT_FAILURE : EXIT_SUCCESS

// Behavior-driven development macros for Given, When, Then structure

/**
 * @brief Macro for defining a Given step in a behavior-driven development test.
 * 
 * This macro is used to define a Given step in a behavior-driven development test.
 * The Given step is used to specify the initial context of a test case.
 * 
 * @param description The description of the Given step.
 */
#define _GIVEN(description) \
    if (0) { \
        printf(FOSSIL_TEST_COLOR_MAGENTA "Given %s\n" FOSSIL_TEST_COLOR_RESET, description); \
    }

/**
 * @brief Macro for defining a When step in a behavior-driven development test.
 * 
 * This macro is used to define a When step in a behavior-driven development test.
 * The When step is used to specify the action that is being tested.
 * 
 * @param description The description of the When step.
 */
#define _WHEN(description) \
    if (0) { \
        printf(FOSSIL_TEST_COLOR_MAGENTA "When %s\n" FOSSIL_TEST_COLOR_RESET, description); \
    }

/**
 * @brief Macro for defining a Then step in a behavior-driven development test.
 * 
 * This macro is used to define a Then step in a behavior-driven development test.
 * The Then step is used to specify the expected outcome of a test case.
 * 
 * @param description The description of the Then step.
 */
#define _THEN(description) \
    if (0) { \
        printf(FOSSIL_TEST_COLOR_MAGENTA "Then %s\n" FOSSIL_TEST_COLOR_RESET, description); \
    }

#ifdef __cplusplus
}
#endif

#endif
