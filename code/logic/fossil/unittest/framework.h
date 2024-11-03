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
#ifndef FOSSIL_TEST_FRAMEWORK_H
#define FOSSIL_TEST_FRAMEWORK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "unittest.h"

/**
 * Macro to define a test suite.
 * This macro is used to declare a test suite, which is a collection of test
 * cases that are related to each other. The test suite can be executed as a
 * whole to verify the correctness of a group of functionalities.
 */
#define FOSSIL_TEST_SUITE(name) \
    _FOSSIL_TEST_SUITE(name)

/**
 * Macro to define a setup function for a test.
 * This macro is used to declare a setup function that will be executed before
 * each test case in a test suite. The setup function should contain the logic
 * to initialize the environment or state required for the test cases.
 */
#define FOSSIL_SETUP(name) \
    _FOSSIL_TEST_SETUP(name)

/**
 * Macro to define a teardown function for a test.
 * This macro is used to declare a teardown function that will be executed after
 * each test case in a test suite. The teardown function should contain the logic
 * to clean up the environment or state after the test cases have been executed.
 */
#define FOSSIL_TEARDOWN(name) \
    _FOSSIL_TEST_TEARDOWN(name)

/**
 * Macro to define a test group.
 * This macro is used to declare a test group, which is a higher-level grouping
 * of test suites. Test groups can be used to organize test suites into logical
 * categories for easier management and execution.
 */
#define FOSSIL_TEST_GROUP(name) \
    _FOSSIL_TEST_GROUP(name)

/**
 * Macro to import a test.
 * This macro is used to import a test case or test suite from another module
 * or file. It allows for the reuse of test cases and test suites across
 * different parts of the project.
 */
#define FOSSIL_TEST_IMPORT(name) \
    _FOSSIL_TEST_IMPORT(name)

/**
 * Macro to export a test.
 * This macro is used to export a test case or test suite so that it can be
 * imported and used in other modules or files. It facilitates the sharing of
 * test cases and test suites across the project.
 */
#define FOSSIL_TEST_EXPORT(name) \
    _FOSSIL_TEST_EXPORT(name)

/**
 * Macro to define a test case.
 * This macro is used to declare a test case function that will be executed
 * as part of the test suite. The test case function should contain the logic
 * to verify the correctness of a specific functionality.
 */
#define FOSSIL_TEST(name) \
    _FOSSIL_TEST_CASE(name)

/**
 * Macro to add a test function to a test queue.
 * This macro is used to add a test function to a test queue, which is a
 * collection of test functions that will be executed in sequence. The test
 * queue allows for the orderly execution of multiple test functions.
 */
#define FOSSIL_TEST_ADD(queue, test_func) \
    _FOSSIL_TEST_ADD(queue, test_func)

/**
 * Macro to add a test function to a test queue with a suite.
 * This macro is used to add a test function to a test queue, specifying the
 * test suite to which the test function belongs. It allows for the organization
 * of test functions within their respective test suites.
 */
#define FOSSIL_TEST_ADDF(queue, test_func, suite) \
    _FOSSIL_TEST_ADDF(queue, test_func, suite)

/**
 * Macro to assume a condition in a test runner.
 * This macro is used to assert that a specific condition is true within a test
 * runner. If the condition is false, the test runner will output the specified
 * message and may abort the execution of the test case or test suite.
 */
#define FOSSIL_TEST_ASSUME(runner, condition, message) \
    _FOSSIL_TEST_ASSUME(runner, condition, message)

#ifdef __cplusplus
}
#endif

#endif
