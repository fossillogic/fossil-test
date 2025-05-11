/*
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop high-
 * performance, cross-platform applications and libraries. The code contained
 * herein is subject to the terms and conditions defined in the project license.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#ifndef FOSSIL_TEST_H
#define FOSSIL_TEST_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

// --- Return codes ---
enum {
    FOSSIL_PIZZA_SUCCESS = 0,
    FOSSIL_PIZZA_FAILURE = -1
};

typedef enum {
    FOSSIL_PIZZA_CASE_EMPTY = 0,
    FOSSIL_PIZZA_CASE_PASS,
    FOSSIL_PIZZA_CASE_FAIL,
    FOSSIL_PIZZA_CASE_TIMEOUT,
    FOSSIL_PIZZA_CASE_SKIPPED,
    FOSSIL_PIZZA_CASE_UNEXPECTED
} fossil_pizza_case_result_t;

// --- Pizza Data Types ---
typedef enum {
    FOSSIL_PIZZA_TYPE_I8,
    FOSSIL_PIZZA_TYPE_I16,
    FOSSIL_PIZZA_TYPE_I32,
    FOSSIL_PIZZA_TYPE_I64,
    FOSSIL_PIZZA_TYPE_U8,
    FOSSIL_PIZZA_TYPE_U16,
    FOSSIL_PIZZA_TYPE_U32,
    FOSSIL_PIZZA_TYPE_U64,
    FOSSIL_PIZZA_TYPE_HEX,
    FOSSIL_PIZZA_TYPE_OCTAL,
    FOSSIL_PIZZA_TYPE_FLOAT,
    FOSSIL_PIZZA_TYPE_DOUBLE,
    FOSSIL_PIZZA_TYPE_WSTR,
    FOSSIL_PIZZA_TYPE_CSTR,
    FOSSIL_PIZZA_TYPE_CCHAR,
    FOSSIL_PIZZA_TYPE_WCHAR,
    FOSSIL_PIZZA_TYPE_BOOL,
    FOSSIL_PIZZA_TYPE_SIZE,
    FOSSIL_PIZZA_TYPE_ANY
} fossil_pizza_type_t;

typedef struct {
    char *data;
    bool mutable_flag;
} fossil_pizza_value_t;

typedef struct {
    char* name;
    char* description;
    char* id;
} fossil_pizza_attribute_t;

typedef struct {
    fossil_pizza_type_t type;
    fossil_pizza_value_t value;
    fossil_pizza_attribute_t attribute;
} fossil_pizza_t;

// --- Score Struct ---
typedef struct {
    int passed;
    int failed;
    int skipped;
    int timeout;
    int unexpected;
    int empty;
} fossil_pizza_score_t;

// --- Test Case ---
typedef struct {
    char* name;
    char* tags;
    char* criteria;
    void (*setup)(void);
    void (*teardown)(void);
    void (*run)(void);
    uint64_t elapsed_ns;
    fossil_pizza_case_result_t result;
} fossil_pizza_case_t;

// In fossil_pizza_suite_t
typedef struct {
    char* suite_name;
    fossil_pizza_case_t* cases;
    size_t count;
    size_t capacity;
    void (*setup)(void);
    void (*teardown)(void);
    uint64_t time_elapsed_ns;
    int total_score;
    int total_possible;
    fossil_pizza_score_t score;
} fossil_pizza_suite_t;

// In fossil_pizza_engine_t
typedef struct {
    fossil_pizza_suite_t* suites;
    size_t count;
    size_t capacity;
    int score_total;
    int score_possible;
    fossil_pizza_score_t score;
    fossil_pizza_pallet_t pallet;
} fossil_pizza_engine_t;

// --- Initialization ---

/** * Initializes a new fossil_pizza_engine_t instance.
 * @param engine Pointer to the engine to initialize.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_start(fossil_pizza_engine_t* engine, int argc, char** argv);

// --- Adding Test Suites and Cases ---

/** Adds a test suite to the engine.
 * @param engine Pointer to the engine instance.
 * @param suite The suite to add.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_add_suite(fossil_pizza_engine_t* engine, fossil_pizza_suite_t suite);

/** Adds a test case to a suite.
 * @param suite Pointer to the suite instance.
 * @param test_case Pointer to the test case to add.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_add_case(fossil_pizza_suite_t* suite, fossil_pizza_case_t test_case);

// --- Execution ---

/** Runs a single test suite.
 * @param suite Pointer to the suite instance.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_run_suite(const fossil_pizza_engine_t* engine, fossil_pizza_suite_t* suite);

/** Runs all test suites in the engine.
 * @param engine Pointer to the engine instance.
 * @return 0 on success, -1 on failure.
 */
int fossil_pizza_run_all(fossil_pizza_engine_t* engine);

// --- Summary + Teardown ---

/** Prints a summary of the test results.
 * @param engine Pointer to the engine instance.
 */
void fossil_pizza_summary(const fossil_pizza_engine_t* engine);

/** Cleans up and ends the test engine.
 * @param engine Pointer to the engine instance.
 */
int32_t fossil_pizza_end(fossil_pizza_engine_t* engine);

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
void pizza_test_assert_internal(bool condition, const char *message, const char *file, int line, const char *func);

// *********************************************************************************************
// internal messages
// *********************************************************************************************

/**
 * @brief Internal function to handle the "given" step in a test case.
 * 
 * This function is used to set up the context for a test case. It is not
 * intended to be called directly.
 * 
 * @param description The description of the given step.
 */
void _given(const char *description);

/**
 * @brief Internal function to handle the "when" step in a test case.
 * 
 * This function is used to set up the action for a test case. It is not
 * intended to be called directly.
 * 
 * @param description The description of the when step.
 */
void _when(const char *description);

/**
 * @brief Internal function to handle the "then" step in a test case.
 * 
 * This function is used to set up the expected outcome for a test case. It is
 * not intended to be called directly.
 * 
 * @param description The description of the then step.
 */
void _then(const char *description);

/**
 * @brief Internal function to handle the "skip" step in a test case.
 * 
 * This function is used to skip a test case. It is not intended to be called
 * directly.
 * 
 * @param description The description of the skip step.
 */
void _on_skip(const char *description);

#ifdef __cplusplus
}
#endif

/** @brief Macro to define a test case.
 * 
 * This macro is used to define a test case, which is a single unit of testing
 * that verifies a specific functionality or behavior. The test case can be
 * executed independently or as part of a test suite.
 * 
 * @param test_name The name of the test case to define.
 */

#ifdef __cplusplus
#define FOSSIL_TEST(test_name) \
    extern "C" void test_name##_run(void); \
    static fossil_pizza_case_t test_case_##test_name = { \
        (cstr)#test_name, \
        (cstr)"fossil", \
        (cstr)"std", \
        nullptr, \
        nullptr, \
        test_name##_run, \
        0, \
        FOSSIL_PIZZA_CASE_EMPTY \
    }; \
    extern "C" void test_name##_run(void)
#else
#define FOSSIL_TEST(test_name) \
    void test_name##_run(void); \
    static fossil_pizza_case_t test_case_##test_name = { \
        .name = #test_name, \
        .tags = "fossil", \
        .criteria = "std", \
        .setup = NULL, \
        .teardown = NULL, \
        .run = test_name##_run, \
        .elapsed_ns = 0, \
        .result = FOSSIL_PIZZA_CASE_EMPTY \
    }; \
    void test_name##_run(void)
#endif

/** @brief Macro to set a test case's tags.
 * 
 * This macro is used to specify tags for a test case. Tags can be used to
 * categorize or filter test cases based on specific criteria.
 * 
 * @param test_name The name of the test case.
 * @param tags The tags to assign to the test case.
 */
#define FOSSIL_TEST_SET_TAGS(test_name, tags) \
    test_case_##test_name.tags = tags

/** @brief Macro to set a test case's skip message.
 * 
 * This macro is used to specify a skip message for a test case. The skip
 * message indicates that the test case is intentionally skipped and provides
 * a reason for the skip.
 * 
 * @param test_name The name of the test case.
 * @param skip The skip message to assign to the test case.
 */
#define FOSSIL_TEST_SET_SKIP(test_name, skip) \
    test_case_##test_name.result = FOSSIL_PIZZA_CASE_SKIPPED; \
    test_case_##test_name.tags = skip \
    test_case_##test_name.teardown = _on_skip(skip)

/** @brief Macro to set a test case's criteria.
 * 
 * This macro is used to specify criteria for a test case. The criteria can be
 * used to filter or categorize test cases based on specific conditions or
 * requirements.
 * 
 * @param test_name The name of the test case.
 * @param criteria The criteria to assign to the test case.
 */
#define FOSSIL_TEST_SET_CRITERIA(test_name, criteria) \
    test_case_##test_name.criteria = criteria

/** @brief Macro to set a test case's setup function.
 * 
 * This macro is used to specify a setup function for a test case. The setup
 * function will be called before the test case is executed, allowing for any
 * necessary initialization or preparation.
 * 
 * @param test_name The name of the test case.
 * @param before The name of the setup function to call before the test case.
 */
#define FOSSIL_TEST_SET_BEFORE(test_name, before) \
    test_case_##test_name.setup = setup_before_##before

/** @brief Macro to set a test case's setup function.
 * 
 * This macro is used to specify a setup function for a test case. The setup
 * function will be called before the test case is executed, allowing for any
 * necessary initialization or preparation.
 * 
 * @param test_name The name of the test case.
 * @param before The name of the setup function to call before the test case.
 */
#define FOSSIL_TEST_SET_AFTER(test_name, after) \
    test_case_##test_name.teardown = teardown_after_##after

/** @brief Macro to define a test suite.
 * 
 * This macro is used to define a test suite, which is a collection of test cases
 * that are related to each other. The test suite can be executed as a whole to
 * verify the correctness of a group of functionalities.
 * 
 * @param suite_name The name of the suite to define.
 */
#ifdef __cplusplus
#define FOSSIL_SUITE(suite) \
    void setup_##suite(void); \
    void teardown_##suite(void); \
    static fossil_pizza_suite_t suite_##suite { \
        (cstr)#suite, \
        nullptr, \
        0, \
        0, \
        setup_##suite, \
        teardown_##suite, \
        0, \
        0, \
        0, \
        {0, 0, 0, 0, 0, 0} \
    }
#else
#define FOSSIL_SUITE(suite) \
    void setup_##suite(void); \
    void teardown_##suite(void); \
    static fossil_pizza_suite_t suite_##suite = { \
        .suite_name = #suite, \
        .cases = NULL, \
        .count = 0, \
        .capacity = 0, \
        .setup = setup_##suite, \
        .teardown = teardown_##suite, \
        .time_elapsed_ns = 0, \
        .total_score = 0, \
        .total_possible = 0, \
        .score = {0, 0, 0, 0, 0, 0} \
    }
#endif

/** @brief Macro to define a test setup function.
 * 
 * This macro is used to define a setup function for a test case or suite. The
 * setup function will be called before the test case or suite is executed, and
 * can be used to initialize resources or set up the test environment.
 * 
 * @param test_setup The name of the setup function to define.
 */
#define FOSSIL_SETUP(test_setup) \
    void setup_##test_setup(void)

/** @brief Macro to define a test setup function.
 * 
 * This macro is used to define a setup function for a test case or suite. The
 * setup function will be called before the test case or suite is executed, and
 * can be used to initialize resources or set up the test environment.
 * 
 * @param test_setup The name of the setup function to define.
 */
#define FOSSIL_TEARDOWN(test_teardown) \
    void teardown_##test_teardown(void)

/** @brief Macro to define a test setup function.
 * 
 * This macro is used to define a setup function for a test case or suite. The
 * setup function will be called before the test case or suite is executed, and
 * can be used to initialize resources or set up the test environment.
 * 
 * @param test_setup The name of the setup function to define.
 */
#define FOSSIL_BEFORE(test_setup) \
    void setup_before_##test_setup(void)

/** @brief Macro to define a test teardown function.
 * 
 * This macro is used to define a teardown function for a test case or suite. The
 * teardown function will be called after the test case or suite has been executed, and
 * can be used to clean up resources or reset the test environment.
 *
 * @param test_teardown The name of the teardown function to define.
 */
#define FOSSIL_AFTER(test_teardown) \
    void teardown_after_##test_teardown(void)

/** @brief Macro to add a test case to a specific suite.
 * 
 * This macro is used to add a test case to a specific test suite that has been
 * defined in the test engine. It will link the test case to the suite and
 * ensure it is executed when the suite is run.
 * 
 * @param suite The name of the suite to which the test case will be added.
 * @param test_case The name of the test case to add.
 */
#define FOSSIL_TEST_ADD(suite, test_case) \
    fossil_pizza_add_case(&suite_##suite, test_case_##test_case)

/** @brief Macro to run a specific test suite.
 * 
 * This macro is used to run a specific test suite that has been defined in the
 * test engine. It will execute all test cases within the specified suite and
 * print the results.
 * 
 * @param suite The name of the suite to run.
 */
#define FOSSIL_RUN_SUITE(suite) \
    fossil_pizza_run_suite(&engine, &suite_##suite)

/** @brief Macro to start the test engine.
 * 
 * This macro is used to initialize and start the test engine. It should be called
 * at the beginning of the test execution to set up the environment for running
 * tests.
 * 
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 */
#define FOSSIL_TEST_START(argc, argv) \
    fossil_pizza_engine_t engine; \
    if (fossil_pizza_start(&engine, argc, argv) != FOSSIL_PIZZA_SUCCESS) { \
        return FOSSIL_PIZZA_FAILURE; \
    }

/** @brief Macro to print a summary of the test results.
 * 
 * This macro is used to print a summary of the test results after all tests have
 * been run. It provides an overview of the number of tests passed, failed, and
 * skipped.
 * 
 * @param engine The engine instance containing the test results.
 */
#define FOSSIL_SUMMARY() \
    fossil_pizza_summary(&engine)

/** @brief Macro to run all test suites in the engine.
 * 
 * This macro is used to run all test suites that have been added to the test
 * engine. It will execute each suite and its associated test cases, collecting
 * results and printing a summary at the end.
 * 
 * @param engine The engine instance containing the test suites.
 */
#define FOSSIL_RUN_ALL() \
    fossil_pizza_run_all(&engine)

/** @brief Macro to end the test engine.
 * 
 * This macro is used to clean up and end the test engine after all tests have
 * been run. It should be called at the end of the test execution.
 * 
 * @param engine The engine instance to end.
 */
#define FOSSIL_END() \
    fossil_pizza_end(&engine)


/**
 * @brief Macro to register a test suite with the engine.
 * 
 * This macro is used to register a test suite with the test engine. It will
 * ensure that the suite is added to the engine and can be executed when the
 * test runner is run.
 * 
 * @param suite The name of the suite to register.
 */
#define FOSSIL_TEST_REGISTER(suite) \
    fossil_pizza_add_suite(engine, suite_##suite)

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
#define FOSSIL_TEST_GROUP(name) \
    extern "C" void name##_test_group(fossil_pizza_engine_t *engine)
#else
#define FOSSIL_TEST_GROUP(name) \
    void name##_test_group(fossil_pizza_engine_t *engine)
#endif

/**
 * @brief Macro to export a test group.
 * 
 * This macro is used to export a test group from a test file. The test group
 * will be available to other test files that import it.
 * 
 * @param name The name of the test group to export.
 */
#ifdef __cplusplus
#define FOSSIL_TEST_EXPORT(name) \
    extern "C" void name##_test_group(fossil_pizza_engine_t *engine)
#else
#define FOSSIL_TEST_EXPORT(name) \
    void name##_test_group(fossil_pizza_engine_t *engine)
#endif

/**
 * @brief Macro to import a test group.
 * 
 * This macro is used to import a test group into the test runner. The test group
 * will be executed when the test runner is run.
 * 
 * @param name The name of the test group to import.
 */
#ifdef __cplusplus
#define FOSSIL_TEST_IMPORT(name) \
    extern "C" void name##_test_group(fossil_pizza_engine_t *engine)
#else
#define FOSSIL_TEST_IMPORT(name) \
    name##_test_group(&engine)
#endif

/**
 * @brief Macro to assume a condition in a test runner.
 * This macro is used to assert that a specific condition is true within a test
 * runner. If the condition is false, the test runner will output the specified
 * message and may abort the execution of the test case or test suite.
 */
#define FOSSIL_TEST_ASSUME(condition, message) \
    pizza_test_assert_internal((condition), (message), __FILE__, __LINE__, __func__)

/**
 * @brief Macro to assume a condition in a test runner.
 * This macro is used to assert that a specific condition is true within a test
 * runner. If the condition is false, the test runner will output the specified
 * message and may abort the execution of the test case or test suite.
 */
#define FOSSIL_TEST_ASSERT(condition, message) \
    pizza_test_assert_internal((condition), (message), __FILE__, __LINE__, __func__)


/**
 * @brief Macro for defining a Given step in a behavior-driven development test.
 * 
 * This macro is used to define a Given step in a behavior-driven development test.
 * The Given step is used to specify the initial context of a test case.
 * 
 * @param description The description of the Given step.
 */
#define GIVEN(description) \
    if (0) { \
        _given(description); \
    }

/**
 * @brief Macro for defining a When step in a behavior-driven development test.
 * 
 * This macro is used to define a When step in a behavior-driven development test.
 * The When step is used to specify the action that is being tested.
 * 
 * @param description The description of the When step.
 */
#define WHEN(description) \
    if (0) { \
        _when(description); \
    }

/**
 * @brief Macro for defining a Then step in a behavior-driven development test.
 * 
 * This macro is used to define a Then step in a behavior-driven development test.
 * The Then step is used to specify the expected outcome of a test case.
 * 
 * @param description The description of the Then step.
 */
#define THEN(description) \
    if (0) { \
        _then(description); \
    }

#endif
