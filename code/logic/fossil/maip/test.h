/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2013
 *
 * Copyright (C) 2013-Current Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_TEST_H
#define FOSSIL_TEST_H

#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

// --- Return codes ---
enum
{
    FOSSIL_MAIP_SUCCESS = 0,
    FOSSIL_MAIP_FAILURE = -1
};

typedef enum
{
    FOSSIL_MAIP_CASE_EMPTY = 0,
    FOSSIL_MAIP_CASE_PASS,
    FOSSIL_MAIP_CASE_FAIL,
    FOSSIL_MAIP_CASE_TIMEOUT,
    FOSSIL_MAIP_CASE_SKIPPED,
    FOSSIL_MAIP_CASE_UNEXPECTED
} fossil_maip_state_t;

// --- Score Struct ---
typedef struct
{
    int passed;
    int failed;
    int skipped;
    int timeout;
    int unexpected;
    int empty;
} fossil_maip_score_t;

// --- Test Case ---
typedef struct
{
    char *name;     // Test name
    char *tags;     // Comma-separated tags
    char *criteria; // Description or expectations

    void (*setup)(void);    // Optional setup
    void (*teardown)(void); // Optional teardown
    void (*run)(void);      // Test execution function

    uint64_t elapsed_ns;               // Timing in nanoseconds
    int64_t priority;                  // Priority level (lower = higher priority)
    fossil_maip_state_t state; // Outcome of the test case
} fossil_maip_case_t;

// --- Test Suite ---
typedef struct
{
    char *name;
    fossil_maip_case_t *cases;
    size_t count;
    size_t capacity;

    void (*setup)(void);
    void (*teardown)(void);

    uint64_t time_elapsed_ns;
    int total_score;
    int total_possible;

    fossil_maip_score_t score;
} fossil_maip_suite_t;

// In fossil_maip_engine_t
typedef struct
{
    fossil_maip_suite_t *suites;
    size_t count;
    size_t capacity;

    int score_total;
    int score_possible;

    fossil_maip_score_t score;

    fossil_maip_pallet_t pallet; // CLI + config
} fossil_maip_engine_t;

// --- Initialization ---

/** * 
 * @brief Initializes a new fossil_maip_engine_t instance.
 * 
 * @param engine Pointer to the engine to initialize.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @note This function sets up the test engine, preparing it to run test suites and cases.
 */
FOSSIL_MAIP_API int fossil_maip_start(fossil_maip_engine_t *engine, int argc, char **argv);

// --- Adding Test Suites and Cases ---

/** 
 * @brief Adds a test suite to the engine.
 * 
 * @param engine Pointer to the engine instance.
 * @param suite The suite to add.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @note The engine takes ownership of the suite and its cases. The suite's case array is copied to ensure that the engine can manage its own memory.
 */
FOSSIL_MAIP_API int fossil_maip_add_suite(fossil_maip_engine_t *engine, fossil_maip_suite_t suite);

/** 
 * @brief Adds a test case to a suite.
 * 
 * @param suite Pointer to the suite instance.
 * @param test_case Pointer to the test case to add.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @note The suite takes ownership of the test case. The test case is copied into the suite's case array, and the suite manages its own memory.
 */
FOSSIL_MAIP_API int fossil_maip_add_case(fossil_maip_suite_t *suite, fossil_maip_case_t test_case);

// --- Execution ---

/** 
 * @brief Runs a single test suite.
 * 
 * @param engine Pointer to the engine instance.
 * @param suite Pointer to the suite instance.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @note This function executes all test cases in the suite, applying any setup and teardown functions defined for the suite. It also updates the suite's score and timing information.
 */
FOSSIL_MAIP_API int fossil_maip_run_suite(const fossil_maip_engine_t *engine, fossil_maip_suite_t *suite);

/** 
 * @brief Runs all test suites in the engine.
 * 
 * @param engine Pointer to the engine instance.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @note This function iterates through all test suites in the engine, executing each one and accumulating the overall score and timing information. It is the main entry point for running all tests.
 */
FOSSIL_MAIP_API int fossil_maip_run_all(fossil_maip_engine_t *engine);

// --- Summary + Teardown ---

/** 
 * @brief Prints a summary of the test results.
 * 
 * @param engine Pointer to the engine instance.
 * 
 * @note This function outputs a summary of the test results, including the number of passed, failed, skipped, and unexpected test cases. It also provides timing information and any AI-generated feedback if applicable.
 */
FOSSIL_MAIP_API void fossil_maip_summary(const fossil_maip_engine_t *engine);

/** 
 * @brief Cleans up and ends the test engine.
 * 
 * @param engine Pointer to the engine instance.
 * 
 * @return 0 on success, -1 on failure.
 * 
 * @note This function releases all memory allocated for the test suites and cases, and performs any necessary teardown operations. It should be called after all tests have been executed and the summary has been printed.
 */
FOSSIL_MAIP_API int32_t fossil_maip_end(fossil_maip_engine_t *engine);

/**
 * @brief Internal function to handle assertions with anomaly detection.
 *
 * @param condition The condition to check.
 * @param message The message to display if the condition is false.
 * @param file The file name where the assertion occurred.
 * @param line The line number where the assertion occurred.
 * @param func The function name where the assertion occurred.
 * 
 * @note This function is used internally by the test framework to handle assertions and detect anomalies. It is not intended to be called directly.
 */
FOSSIL_MAIP_API void maip_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func);

/**
 * @brief Internal function to handle assertions with message formatting.
 *
 * @param message The message to format.
 * @param ... Additional arguments for formatting the message.
 * 
 * @return A formatted message string.
 * 
 * @note This function is used internally by the test framework to format assertion messages. It is not intended to be called directly.
 */
FOSSIL_MAIP_API char *maip_test_assert_messagef(const char *message, ...);

// *********************************************************************************************
// internal messages
// *********************************************************************************************

FOSSIL_MAIP_API void _given(const char *description);

FOSSIL_MAIP_API void _when(const char *description);

FOSSIL_MAIP_API void _and(const char *description);

FOSSIL_MAIP_API void _then(const char *description);

FOSSIL_MAIP_API void _subcase(const char *description);

FOSSIL_MAIP_API void _on_skip(const char *description);

#ifdef __cplusplus
}
#endif

// *********************************************************************************************
// Private API Macros
// *********************************************************************************************

#ifdef __cplusplus
#define _FOSSIL_TEST(test_name)                          \
    extern "C" void test_name##_run(void);               \
    static fossil_maip_case_t test_case_##test_name = { \
        (char *)#test_name,                              \
        (char *)"fossil",                                \
        (char *)"name",                                  \
        nullptr,                                         \
        nullptr,                                         \
        test_name##_run,                                 \
        0,                                               \
        0,                                               \
        FOSSIL_MAIP_CASE_EMPTY};                        \
    extern "C" void test_name##_run(void)
#else
#define _FOSSIL_TEST(test_name)                          \
    void test_name##_run(void);                          \
    static fossil_maip_case_t test_case_##test_name = { \
        .name = #test_name,                              \
        .tags = "fossil",                                \
        .criteria = "name",                              \
        .setup = NULL,                                   \
        .teardown = NULL,                                \
        .run = test_name##_run,                          \
        .elapsed_ns = 0,                                 \
        .priority = 0,                                   \
        .state = FOSSIL_MAIP_CASE_EMPTY};              \
    void test_name##_run(void)
#endif

#ifdef __cplusplus
#define _FOSSIL_TEST_DEPEND_ON(test_name, dep_cases)
#define _FOSSIL_TEST_PARAM(test_name, params)
#else

#endif

#define _FOSSIL_TEST_SET_TAGS(test_name, tags) \
    test_case_##test_name.tags = tags

#define _FOSSIL_TEST_SET_SKIP(test_name, skip)                \
    test_case_##test_name.state = FOSSIL_MAIP_CASE_SKIPPED; \
    test_case_##test_name.tags = skip                         \
                                     test_case_##test_name.teardown = _on_skip(skip)

#define _FOSSIL_TEST_SET_CRITERIA(test_name, criteria) \
    test_case_##test_name.criteria = criteria

#define _FOSSIL_TEST_SET_BEFORE(test_name, before) \
    test_case_##test_name.setup = setup_before_##before

#define _FOSSIL_TEST_SET_AFTER(test_name, after) \
    test_case_##test_name.teardown = teardown_after_##after

#ifdef __cplusplus
#define _FOSSIL_SUITE(suite)                                \
    void setup_##suite(void);                               \
    void teardown_##suite(void);                            \
    static fossil_maip_suite_t suite_##suite               \
    {                                                       \
        (char *)#suite,                                     \
            nullptr,                                        \
            0,                                              \
            0,                                              \
            setup_##suite,                                  \
            teardown_##suite,                               \
            0,                                              \
            0,                                              \
            0,                                              \
            {0, 0, 0, 0, 0, 0}}
#else
#define _FOSSIL_SUITE(suite)                      \
    void setup_##suite(void);                     \
    void teardown_##suite(void);                  \
    static fossil_maip_suite_t suite_##suite = { \
        .name = #suite,                     \
        .cases = NULL,                            \
        .count = 0,                               \
        .capacity = 0,                            \
        .setup = setup_##suite,                   \
        .teardown = teardown_##suite,             \
        .time_elapsed_ns = 0,                     \
        .total_score = 0,                         \
        .total_possible = 0,                      \
        .score = {0, 0, 0, 0, 0, 0}}
#endif

#define _FOSSIL_SETUP(test_setup) \
    inline void setup_##test_setup(void)

#define _FOSSIL_TEARDOWN(test_teardown) \
    inline void teardown_##test_teardown(void)

#define _FOSSIL_BEFORE(test_setup) \
    inline void setup_before_##test_setup(void)

#define _FOSSIL_AFTER(test_teardown) \
    inline void teardown_after_##test_teardown(void)

#define _FOSSIL_ADD_TEST(suite, test_case) \
    fossil_maip_add_case(&suite_##suite, test_case_##test_case)

#define _FOSSIL_RUN_SUITE(suite) \
    fossil_maip_run_suite(&engine, &suite_##suite)

#define _FOSSIL_TEST_START(argc, argv)                                   \
    fossil_maip_engine_t engine;                                        \
    if (fossil_maip_start(&engine, argc, argv) != FOSSIL_MAIP_SUCCESS) \
    {                                                                    \
        return FOSSIL_MAIP_FAILURE;                                     \
    }

#define _FOSSIL_SUMMARY() \
    fossil_maip_summary(&engine)

#define _FOSSIL_RUN_ALL() \
    fossil_maip_run_all(&engine)

#define _FOSSIL_END() \
    fossil_maip_end(&engine)

#define _FOSSIL_ADD_SUITE(suite) \
    fossil_maip_add_suite(engine, suite_##suite)

#ifdef __cplusplus
#define _FOSSIL_TEST_GROUP(name) \
    extern "C" void name##_test_group(fossil_maip_engine_t *engine)
#else
#define _FOSSIL_TEST_GROUP(name) \
    void name##_test_group(fossil_maip_engine_t *engine)
#endif

#ifdef __cplusplus
#define _FOSSIL_TEST_EXPORT(name) \
    extern "C" void name##_test_group(fossil_maip_engine_t *engine)
#else
#define _FOSSIL_TEST_EXPORT(name) \
    void name##_test_group(fossil_maip_engine_t *engine)
#endif

#ifdef __cplusplus
#define _FOSSIL_TEST_IMPORT(name) \
    extern "C" void name##_test_group(fossil_maip_engine_t *engine)
#else
#define _FOSSIL_TEST_IMPORT(name) \
    name##_test_group(&engine)
#endif

#define _FOSSIL_TEST_ASSUME(condition, message) \
    maip_test_assert_internal((condition), (message), __FILE__, __LINE__, __func__)

#define _FOSSIL_TEST_ASSERT(condition, message) \
    maip_test_assert_internal((condition), (message), __FILE__, __LINE__, __func__)

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// C23: __VA_OPT__ is available
#define _FOSSIL_TEST_ASSUME_MESSAGE(message, ...) \
    maip_test_assert_messagef((message)__VA_OPT__(, __VA_ARGS__))
#else
// Portable workaround: always require at least one argument after 'message'
#define _FOSSIL_TEST_ASSUME_MESSAGE(...) \
    maip_test_assert_messagef(__VA_ARGS__)
#endif

#define _GIVEN(description)  \
    if (0)                   \
    {                        \
        _given(description); \
    }

#define _WHEN(description)  \
    if (0)                  \
    {                       \
        _when(description); \
    }

#define _AND(description)   \
    if (0)                  \
    {                       \
        _and(description);  \
    }

#define _THEN(description)  \
    if (0)                  \
    {                       \
        _then(description); \
    }

#define _FOSSIL_SUBCASE(description) \
    _subcase(description);           \
    if (true)                        \
        for (const char *__subcase_desc = description; __subcase_desc; __subcase_desc = NULL)

// *****************************************************************************
// Public API Macros
// *****************************************************************************

/**
 * @brief Defines and registers a test case.
 *
 * Declares a single unit of testing that verifies a specific functionality or
 * behavior. The test case may be executed independently or as part of a suite.
 *
 * @param test_name The name of the test case to define.
 *
 * @note The test name should uniquely identify the test within the containing
 *       source file or test group.
 */
#define FOSSIL_TEST(test_name) \
    _FOSSIL_TEST(test_name)

/**
 * @brief Sets tags for a test case.
 *
 * Associates one or more tags with a test case so it can be categorized and
 * included or excluded when tests are filtered.
 *
 * @param test_name The name of the test case whose tags are to be changed.
 * @param tags The tags to assign to the test case.
 *
 * @note Tag syntax and filtering behavior are determined by the test engine.
 */
#define FOSSIL_TEST_SET_TAGS(test_name, tags) \
    _FOSSIL_TEST_SET_TAGS(test_name, tags)

/**
 * @brief Sets a skip reason for a test case.
 *
 * Marks a test case as intentionally skipped and associates a human-readable
 * reason with the skipped execution.
 *
 * @param test_name The name of the test case whose skip state is to be set.
 * @param skip The message describing why the test is skipped.
 *
 * @note Skipped tests are reported separately and are not treated as failures.
 */
#define FOSSIL_TEST_SET_SKIP(test_name, skip) \
    _FOSSIL_TEST_SET_SKIP(test_name, skip)

/**
 * @brief Sets criteria for a test case.
 *
 * Associates filtering or categorization criteria with a test case. Criteria
 * may be used by the test engine to decide when the test is eligible to run.
 *
 * @param test_name The name of the test case whose criteria are to be changed.
 * @param criteria The criteria to assign to the test case.
 *
 * @note Supported criteria and their semantics depend on the test engine.
 */
#define FOSSIL_TEST_SET_CRITERIA(test_name, criteria) \
    _FOSSIL_TEST_SET_CRITERIA(test_name, criteria)

/**
 * @brief Sets a setup function for a test case.
 *
 * Registers a function that is invoked before the named test case executes.
 * The function can initialize state or allocate resources required by the test.
 *
 * @param test_name The name of the test case to configure.
 * @param before The setup function to call before the test case.
 *
 * @note The setup function must match the callback signature required by the
 *       test engine.
 */
#define FOSSIL_TEST_SET_BEFORE(test_name, before) \
    _FOSSIL_TEST_SET_BEFORE(test_name, before)

/**
 * @brief Sets a teardown function for a test case.
 *
 * Registers a function that is invoked after the named test case completes.
 * The function can release resources or restore state changed by the test.
 *
 * @param test_name The name of the test case to configure.
 * @param after The teardown function to call after the test case.
 *
 * @note The teardown function must match the callback signature required by the
 *       test engine.
 */
#define FOSSIL_TEST_SET_AFTER(test_name, after) \
    _FOSSIL_TEST_SET_AFTER(test_name, after)

/**
 * @brief Defines a test suite.
 *
 * Creates a named collection of related test cases that can be executed together
 * to verify a group of functionalities.
 *
 * @param suite The name of the suite to define.
 *
 * @note Suite names should be unique within the test runner registration scope.
 */
#define FOSSIL_SUITE(suite) \
    _FOSSIL_SUITE(suite)

/**
 * @brief Defines a setup function.
 *
 * Declares a setup function that initializes resources or state before test
 * execution begins for a test case or suite.
 *
 * @param test_setup The name of the setup function to define.
 *
 * @note Exactly when the setup runs is determined by whether it is attached
 *       to a suite or individual test case.
 */
#define FOSSIL_SETUP(test_setup) \
    _FOSSIL_SETUP(test_setup)

/**
 * @brief Defines a teardown function.
 *
 * Declares a teardown function that cleans up resources or restores state after
 * test execution finishes for a test case or suite.
 *
 * @param test_teardown The name of the teardown function to define.
 *
 * @note Teardown should avoid leaving state that could affect later tests.
 */
#define FOSSIL_TEARDOWN(test_teardown) \
    _FOSSIL_TEARDOWN(test_teardown)

/**
 * @brief Defines a function to run before a test scope.
 *
 * Declares a before hook that prepares the environment before a test case or
 * suite begins executing.
 *
 * @param test_setup The name of the before function to define.
 *
 * @note Use FOSSIL_AFTER() to define the corresponding cleanup hook.
 */
#define FOSSIL_BEFORE(test_setup) \
    _FOSSIL_BEFORE(test_setup)

/**
 * @brief Defines a function to run after a test scope.
 *
 * Declares an after hook that cleans up or restores the environment after a
 * test case or suite finishes executing.
 *
 * @param test_teardown The name of the after function to define.
 *
 * @note Use FOSSIL_BEFORE() to define the corresponding setup hook.
 */
#define FOSSIL_AFTER(test_teardown) \
    _FOSSIL_AFTER(test_teardown)

/**
 * @brief Adds a test case to a suite.
 *
 * Registers an existing test case as a member of the named suite so it runs when
 * the suite is executed.
 *
 * @param suite The name of the suite that receives the test case.
 * @param test_case The name of the test case to add.
 *
 * @note Both identifiers must refer to test definitions visible to the runner.
 */
#define FOSSIL_ADD_TEST(suite, test_case) \
    _FOSSIL_ADD_TEST(suite, test_case)

/**
 * @brief Runs a specific test suite.
 *
 * Executes all test cases registered with the named suite and collects their
 * results using the test engine.
 *
 * @param suite The name of the suite to execute.
 *
 * @note The suite must have been defined and registered before this macro runs.
 */
#define FOSSIL_RUN_SUITE(suite) \
    _FOSSIL_RUN_SUITE(suite)

/**
 * @brief Starts the test engine.
 *
 * Initializes the test engine and processes command-line arguments that control
 * test selection and execution.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line argument array.
 *
 * @note Call this before registering or running tests when engine initialization
 *       is required.
 */
#define FOSSIL_TEST_START(argc, argv) \
    _FOSSIL_TEST_START(argc, argv)

/**
 * @brief Prints the test result summary.
 *
 * Outputs aggregate counts and status information for tests that have finished,
 * including passed, failed, and skipped tests.
 *
 * @note Call after test execution and before FOSSIL_END() for a complete summary.
 */
#define FOSSIL_SUMMARY() \
    _FOSSIL_SUMMARY()

/**
 * @brief Runs all registered test suites.
 *
 * Executes every suite and test case registered with the test engine, collecting
 * and reporting results for the complete test run.
 *
 * @note Suites do not run unless they have been registered before this macro.
 */
#define FOSSIL_RUN_ALL() \
    _FOSSIL_RUN_ALL()

/**
 * @brief Ends the test engine.
 *
 * Releases test-engine resources and finalizes the test run. This should be the
 * final test-runner operation after suites and summaries have been handled.
 *
 * @note Do not run tests or print summaries after the engine has been ended.
 */
#define FOSSIL_END() \
    _FOSSIL_END()

/**
 * @brief Registers a test suite with the engine.
 *
 * Adds an already-defined suite to the engine so the suite can be discovered,
 * selected, and executed by the test runner.
 *
 * @param suite The name of the suite to register.
 *
 * @note Registration should occur before suite execution or FOSSIL_RUN_ALL().
 */
#define FOSSIL_ADD_SUITE(suite) \
    _FOSSIL_ADD_SUITE(suite)

/**
 * @brief Defines a test group.
 *
 * Creates a named collection of test cases that can be exported or imported
 * across test source files.
 *
 * @param name The name of the test group to define.
 *
 * @note Group names should be unique within the linking scope used by the runner.
 */
#define FOSSIL_TEST_GROUP(name) \
    _FOSSIL_TEST_GROUP(name)

/**
 * @brief Exports a test group.
 *
 * Makes the named test group available to test runner source files that import
 * it through FOSSIL_TEST_IMPORT().
 *
 * @param name The name of the test group to export.
 *
 * @note Export declarations must correspond to groups defined in the exporting
 *       test source.
 */
#define FOSSIL_TEST_EXPORT(name) \
    _FOSSIL_TEST_EXPORT(name)

/**
 * @brief Imports a test group.
 *
 * Adds the named exported test group to the current test runner so its test
 * cases participate in discovery and execution.
 *
 * @param name The name of the test group to import.
 *
 * @note The named group must be exported by a linked test source file.
 */
#define FOSSIL_TEST_IMPORT(name) \
    _FOSSIL_TEST_IMPORT(name)

/**
 * @brief Makes an assumption in a test runner.
 *
 * Checks whether a condition is valid for continuing the test. If the condition
 * is false, the engine reports the supplied message and applies the engine's
 * assumption failure behavior.
 *
 * @param condition The condition that must evaluate to true.
 * @param message The diagnostic message associated with a failed assumption.
 *
 * @note Assumptions may stop or skip the affected test instead of counting as a
 *       normal assertion failure.
 */
#define FOSSIL_TEST_ASSUME(condition, message) \
    _FOSSIL_TEST_ASSUME(condition, message)

/**
 * @brief Asserts a condition in a test runner.
 *
 * Checks whether a condition is true while a test is executing. If the condition
 * is false, the engine reports the supplied message and records a test failure.
 *
 * @param condition The condition that must evaluate to true.
 * @param message The diagnostic message associated with a failed assertion.
 *
 * @note Assertion behavior, including execution continuation, is controlled by
 *       the test engine implementation.
 */
#define FOSSIL_TEST_ASSERT(condition, message) \
    _FOSSIL_TEST_ASSERT(condition, message)

/**
 * @brief Defines a Given behavior step.
 *
 * Records the initial context or precondition for a behavior-driven development
 * test before an action is performed.
 *
 * @param description The human-readable description of the Given step.
 *
 * @note Given steps should describe the state of the system before the action.
 */
#define GIVEN(description) \
    _GIVEN(description)

/**
 * @brief Defines a When behavior step.
 *
 * Records the action or event being evaluated in a behavior-driven development
 * test.
 *
 * @param description The human-readable description of the When step.
 *
 * @note When steps should describe an observable action rather than an outcome.
 */
#define WHEN(description) \
    _WHEN(description)

/**
 * @brief Defines a Then behavior step.
 *
 * Records the expected outcome or postcondition of a behavior-driven development
 * test after the action has occurred.
 *
 * @param description The human-readable description of the Then step.
 *
 * @note Then steps should state an observable result that can be verified.
 */
#define THEN(description) \
    _THEN(description)

/**
 * @brief Defines an And continuation step.
 *
 * Adds another condition or statement to the behavior-driven step that precedes
 * it, without changing the required Given, When, or Then context.
 *
 * @param description The human-readable description of the continuation step.
 *
 * @note Use AND() after a Given, When, or Then step to extend that step.
 */
#define AND(description)   \
    _AND(description)

/**
 * @brief Defines a subcase for scoped edge-case testing.
 *
 * Creates a scoped subcase within a test case for running variations of an edge
 * case while retaining the test case's surrounding setup and teardown.
 *
 * @param description The human-readable description of the subcase.
 *
 * @note Subcase scope should contain only setup and assertions specific to that
 *       variation of the test.
 */
#define FOSSIL_SUBCASE(description) \
    _FOSSIL_SUBCASE(description)

#endif
